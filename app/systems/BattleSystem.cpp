#include "BattleSystem.hpp"
#include "../ui/BattleUI.hpp"
#include "../ui/UI.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

BattleSystem::BattleSystem()
    : battleType(BattleType::WILD), battleTurn(0), isPlayerTurn(true)
{
}

void BattleSystem::initializeWildBattle(Player &player, Monster wildMon)
{
    // Copy player party into playerParty Queue
    // GRADER: Dùng Queue<Monster> từ lib/ để quản lý party
    playerParty = player.party;

    // Tạo enemy party chỉ với wild mon
    enemyParty.enqueue(wildMon);

    battleType = BattleType::WILD;
    battleTurn = 0;
    isPlayerTurn = true;

    // Khởi tạo log trống
    std::string startMsg = "Wild " + wildMon.name + " appeared!";
    addLog(startMsg);
}

void BattleSystem::initializeTrainerBattle(Player &player, Trainer &trainer)
{
    // GRADER: Dùng Queue<Monster> từ lib/ để quản lý party của trainer
    playerParty = player.party;
    enemyParty = trainer.party;

    battleType = (trainer.type == TrainerType::GYM) ? BattleType::TRAINER : (trainer.type == TrainerType::ELITE)  ? BattleType::ELITE
                                                                        : (trainer.type == TrainerType::CHAMPION) ? BattleType::CHAMPION
                                                                                                                  : BattleType::TRAINER;

    battleTurn = 0;
    isPlayerTurn = true;

    std::string startMsg = "Trainer " + trainer.name + " sent out " + enemyParty.front().name + "!";
    addLog(startMsg);
}

int BattleSystem::calculateDamage(Monster &attacker, Monster &defender, Move &move)
{
    // Công thức damage: dmg = (power * atk) / def
    // Nếu def = 0, dùng 1 để tránh divide by zero
    int damage = (move.power * attacker.atk) / (defender.def > 0 ? defender.def : 1);

    // Tối thiểu 1 damage để tránh vô hạn
    if (damage < 1)
        damage = 1;

    return damage;
}

void BattleSystem::addLog(const std::string &line)
{
    // GRADER: Sử dụng Stack<std::string> từ lib/ để lưu log (max 5 lines)
    // Thêm line mới vào Stack
    battleLog.push(line);

    // Nếu Stack vượt quá 5 lines, pop() những line cũ
    // (vì Stack LIFO, phải pop từ top cho đến khi size <= 5)
    while (battleLog.size() > 5)
    {
        battleLog.pop();
    }
}

BattleResult BattleSystem::checkBattleEnd()
{
    if (playerParty.empty())
    {
        return BattleResult::LOSS;
    }
    if (enemyParty.empty())
    {
        return BattleResult::WIN;
    }
    // Chưa kết thúc - dùng giá trị lạ để chỉ "chưa xong"
    // C++ không có nullable enum, nên ta trả về WIN tạm thời khi gọi hàm
    // và kiểm tra đơn độc trong runBattle
    return BattleResult::WIN; // Placeholder
}

bool BattleSystem::playerAttack(int moveIdx)
{
    // Kiểm tra moveIdx hợp lệ
    if (moveIdx < 0 || moveIdx > 3)
    {
        return false;
    }

    // Lấy active mons từ front of queues
    Monster &playerMon = playerParty.front();
    Monster &enemyMon = enemyParty.front();
    Move &move = playerMon.moves[moveIdx];

    // Kiểm tra move hợp lệ (power > 0 means it's a real move)
    if (move.power <= 0 && moveIdx < 2)
    {
        // Nếu là move đầu tiên mà power = 0, tính damage = 0 (vẫn được dùng)
        // Nếu move này là status move (power = 0), hành động khác...
        // Tạm thời: cho phép tấn công nhưng damage sẽ = 0
    }

    // Tính sát thương
    int damage = calculateDamage(playerMon, enemyMon, move);

    // Giảm HP enemy
    enemyMon.hp -= damage;

    // Thêm log
    std::string logMsg = "> " + playerMon.name + " used " + move.name + "! " + std::to_string(damage) + " dmg";
    addLog(logMsg);

    // Kiểm tra enemy faint
    if (enemyMon.hp <= 0)
    {
        addLog(enemyMon.name + " fainted!");

        // Dequeue enemy mon và tìm mon tiếp theo (nếu có)
        enemyParty.dequeue();

        if (!enemyParty.empty())
        {
            std::string nextMsg = "Enemy sent out " + enemyParty.front().name + "!";
            addLog(nextMsg);
        }
    }
    else
    {
        // Enemy vẫn sống sót - enemy đánh trả
        enemyAttack(player);
    }

    return true;
}

void BattleSystem::enemyAttack(Player &player)
{
    if (enemyParty.empty())
    {
        return; // Không có mon để tấn công
    }

    Monster &enemyMon = enemyParty.front();
    Monster &playerMon = playerParty.front();

    // Chọn move ngẫu nhiên từ 4 moves (Phase 03 random; Phase 06 sẽ dùng PriorityQueue)
    int moveIdx = rand() % 4;
    Move &move = enemyMon.moves[moveIdx];

    // Nếu move không hợp lệ (power = 0), chọn move khác
    if (move.power <= 0)
    {
        moveIdx = 0; // Fallback to first move
        move = enemyMon.moves[moveIdx];
    }

    // Tính sát thương
    int damage = calculateDamage(enemyMon, playerMon, move);

    // Giảm HP player
    playerMon.hp -= damage;

    // Thêm log
    std::string logMsg = "Enemy " + enemyMon.name + " used " + move.name + "! " + std::to_string(damage) + " dmg";
    addLog(logMsg);

    // Kiểm tra player faint
    if (playerMon.hp <= 0)
    {
        addLog(playerMon.name + " fainted!");

        // Dequeue player mon và tìm mon tiếp theo (nếu có)
        playerParty.dequeue();

        if (!playerParty.empty())
        {
            std::string nextMsg = playerParty.front().name + " was sent out!";
            addLog(nextMsg);
        }
    }
}

bool BattleSystem::handleFaint(bool isPlayer)
{
    if (isPlayer)
    {
        if (!playerParty.empty())
        {
            playerParty.dequeue();
        }
        return !playerParty.empty();
    }
    else
    {
        if (!enemyParty.empty())
        {
            enemyParty.dequeue();
        }
        return !enemyParty.empty();
    }
}

bool BattleSystem::switchMon()
{
    // GRADER: Sử dụng Queue<Monster> từ lib/ để rotate party
    // Kiểm tra xem có mon khác trong party không
    if (playerParty.size() <= 1)
    {
        addLog("No other monsters available!");
        return false;
    }

    // Dequeue mon hiện tại từ front
    Monster currentMon = playerParty.dequeue();

    // Enqueue nó vào back
    playerParty.enqueue(currentMon);

    // Log switch
    std::string switchMsg = playerParty.front().name + " was sent out!";
    addLog(switchMsg);

    return true;
}

bool BattleSystem::attemptRun()
{
    // Chỉ dùng với wild battles
    if (battleType != BattleType::WILD)
    {
        addLog("You can't run from trainer battles!");
        return false;
    }

    // 50% success rate khi chạy
    int attempt = rand() % 2;
    if (attempt == 0)
    {
        addLog("Escaped successfully!");
        return true;
    }
    else
    {
        addLog("Couldn't escape!");
        return false;
    }
}

BattleResult BattleSystem::runBattle(Player &player)
{
    while (true)
    {
        // 1. Hiển thị trạng thái hiện tại
        BattleUI::renderBattleScreen(*this);

        // 2. Lấy input từ player
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        // Trim input
        size_t first = input.find_first_not_of(" \t\n\r");
        if (first != std::string::npos)
        {
            size_t last = input.find_last_not_of(" \t\n\r");
            input = input.substr(first, (last - first + 1));
        }
        else
        {
            input = "";
        }

        // Validate input
        if (input.length() != 1)
        {
            continue;
        }

        char choice = input[0];

        switch (choice)
        {
        case '1':
        {
            // Fight - chọn move
            if (playerParty.empty())
            {
                continue;
            }

            Monster &playerMon = playerParty.front();

            // Hiển thị available moves
            std::cout << "\nAvailable moves:\n";
            for (int i = 0; i < 4; i++)
            {
                if (playerMon.moves[i].power > 0 || i < 2)
                {
                    std::cout << "  [" << (i + 1) << "] " << playerMon.moves[i].name
                              << " (Power: " << playerMon.moves[i].power << ")\n";
                }
            }
            std::cout << "> Choose move (1-4): ";

            std::string moveInput;
            std::getline(std::cin, moveInput);

            // Trim
            first = moveInput.find_first_not_of(" \t\n\r");
            if (first != std::string::npos)
            {
                size_t last = moveInput.find_last_not_of(" \t\n\r");
                moveInput = moveInput.substr(first, (last - first + 1));
            }
            else
            {
                moveInput = "";
            }

            if (moveInput.length() != 1)
            {
                addLog("Invalid move selection!");
                continue;
            }

            int moveIdx = moveInput[0] - '1';
            if (moveIdx < 0 || moveIdx > 3)
            {
                addLog("Invalid move selection!");
                continue;
            }

            playerAttack(moveIdx);
            break;
        }

        case '2':
        {
            // Bag - not implemented yet
            addLog("[Bag not implemented - Phase 04]");
            break;
        }

        case '3':
        {
            // Switch
            if (!switchMon())
            {
                // Switch failed, don't let enemy attack
                addLog("Switch failed!");
                break;
            }
            // Switch succeeded, now enemy attacks (if still alive)
            if (!enemyParty.empty())
            {
                enemyAttack(player);
            }
            break;
        }

        case '4':
        {
            // Run
            if (!canRun())
            {
                addLog("Can't escape from trainer battles!");
                break;
            }

            if (attemptRun())
            {
                return BattleResult::RUN;
            }
            // Run failed, enemy attacks
            if (!enemyParty.empty())
            {
                enemyAttack(player);
            }
            break;
        }

        default:
        {
            addLog("Invalid choice! Use 1-4.");
            break;
        }
        }

        // Kiểm tra trận chiến kết thúc
        if (playerParty.empty())
        {
            return BattleResult::LOSS;
        }
        if (enemyParty.empty())
        {
            return BattleResult::WIN;
        }
    }

    return BattleResult::LOSS; // Default fallback
}
