#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP

#include <string>
#include "../entities/Player.hpp"
#include "../entities/Monster.hpp"
#include "../entities/Trainer.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

/**
 * @enum BattleResult
 * @brief Kết quả khi kết thúc trận chiến.
 */
enum class BattleResult
{
    WIN,  ///< Người chơi thắng (hết mons của đối thủ)
    LOSS, ///< Người chơi thua (hết mons trong party)
    RUN   ///< Người chơi chạy trốn (chỉ dùng với wild)
};

/**
 * @enum BattleType
 * @brief Loại trận chiến.
 */
enum class BattleType
{
    WILD,    ///< Gặp wild Pokémon
    TRAINER, ///< Chiến với trainer/gym leader
    ELITE,   ///< Chiến với Elite Four
    CHAMPION ///< Chiến với Champion
};

/**
 * @class BattleSystem
 * @brief Quản lý toàn bộ logic trận chiến turn-based.
 *        Sử dụng Queue<Monster> từ lib/ cho party management (FIFO: front mon fights).
 *        Sử dụng Stack<std::string> từ lib/ cho battle log (max 5 lines).
 */
class BattleSystem
{
private:
    Queue<Monster> playerParty;   ///< GRADER: Queue<Monster> từ lib/ cho player party (FIFO)
    Queue<Monster> enemyParty;    ///< Enemy party (wild or trainer mons)
    Queue<Monster> faintedPlayerMons; ///< Lưu trữ những Pokemon đã fainted để trả về sau trận
    Stack<std::string> battleLog; ///< GRADER: Stack<std::string> từ lib/ cho log (max 5 lines)
    BattleType battleType;        ///< Loại trận chiến
    int battleTurn;               ///< Số lượt đã diễn ra
    bool isPlayerTurn;            ///< Lượt của ai (player=true, enemy=false)
    int totalPlayerMons;          ///< Tổng số Pokemon ban đầu của player
    int totalEnemyMons;           ///< Tổng số Pokemon ban đầu của enemy

    /**
     * @brief Tính sát thương dựa trên công thức: dmg = (power * atk) / def
     * @param attacker Monster tấn công
     * @param defender Monster bị tấn công
     * @param move Đòn đánh dùng
     * @param effectiveness Tham chiếu trả về hệ số khắc hệ để in ra log
     * @return Sát thương
     */
    int calculateDamage(Monster &attacker, Monster &defender, Move &move, float &effectiveness);

    /**
     * @brief Thêm log line vào Stack, duy trì tối đa 5 dòng.
     *        GRADER: Sử dụng Stack<std::string> với cơ chế giới hạn 5 lines.
     * @param line Dòng log cần thêm
     */
    void addLog(const std::string &line);

    /**
     * @brief Kiểm tra xem trận chiến đã kết thúc chưa.
     * @return BattleResult (WIN, LOSS, hoặc -1 nếu chưa kết thúc)
     */
    BattleResult checkBattleEnd();

    /**
     * @brief Xử lý lượt tấn công của enemy (random move selection).
     *        Tính damage sử dụng các queue mons hiện tại từ playerParty và enemyParty.
     *        Phase 03: enemy chọn move ngẫu nhiên.
     *        Phase 06: sẽ dùng PriorityQueue để chọn move tốt nhất.
     */
    void enemyAttack();

    /**
     * @brief Hiển thị thông tin monster hiện tại và HP bar.
     */
    void displayBattleUI();

    /**
     * @brief Áp dụng badge stat boosts lên playerParty trước khi battle bắt đầu.
     *        Theo Gen 1 mechanic: mỗi badge nhân stat tương ứng ×9/8 (≈1.125).
     *        Boulder=Atk, Cascade=Def, Thunder=Spd, Rainbow=Spc,
     *        Soul=Spd, Marsh=Spc, Volcano=Spc, Earth=Def.
     * @param badgeCount Số badge player đang có (0–8)
     */
    void applyBadgeBoosts(int badgeCount);

    /**
     * @brief Xử lý mon faint (HP <= 0).
     * @param isPlayer True nếu mon của player faint, False nếu mon enemy faint
     * @return True nếu vẫn còn mons, False nếu hết mons
     */
    bool handleFaint(bool isPlayer);

public:
    /**
     * @brief Constructor khởi tạo BattleSystem rỗng.
     */
    BattleSystem();

    /**
     * @brief Khởi tạo trận chiến wild encounter.
     * @param player Tham chiếu Player (lấy party)
     * @param wildMon Monster hoang dã cần chiến
     */
    void initializeWildBattle(Player &player, Monster wildMon);

    /**
     * @brief Khởi tạo trận chiến với Trainer/Gym Leader.
     * @param player Tham chiếu Player (lấy party)
     * @param trainer Trainer đối thủ (lấy party của trainer)
     */
    void initializeTrainerBattle(Player &player, Trainer &trainer);

    /**
     * @brief Xử lý tấn công của player. Sử dụng Queue<Monster> và Stack<std::string> để quản lý party và log.
     * @param moveIdx Index của move (0-3) mà player chọn
     * @param player Tham chiếu tới Player để kiểm tra trạng thái (dùng cho enemyAttack call)
     * @return True nếu tấn công thành công, False nếu input không hợp lệ
     */
    bool playerAttack(int moveIdx, Player &player);

    /**
     * @brief Lấy tham chiếu Stack log để display.
     * @return Reference tới battleLog
     */
    Stack<std::string> &getLog() { return battleLog; }

    /**
     * @brief Lấy tham chiếu player party.
     * @return Reference tới playerParty
     */
    Queue<Monster> &getPlayerParty() { return playerParty; }

    /**
     * @brief Lấy tham chiếu enemy party.
     * @return Reference tới enemyParty
     */
    Queue<Monster> &getEnemyParty() { return enemyParty; }

    /**
     * @brief Xử lý switch pokémon (rotate party: dequeue front, enqueue back).
     *        Nếu party chỉ có 1 mon, in thông báo "No other monsters available!"
     * @return True nếu switch thành công, False nếu không có mon khác
     */
    bool switchMon();

    /**
     * @brief Xử lý attempt run (chỉ dùng với wild, 50% success rate).
     * @return True nếu escape thành công, False nếu thất bại
     */
    bool attemptRun();

    /**
     * @brief Vòng lặp trận chiến chính.
     * @param player Tham chiếu Player
     * @return BattleResult (WIN, LOSS, hoặc RUN)
     */
    BattleResult runBattle(Player &player);

    /**
     * @brief Lấy loại trận chiến hiện tại.
     */
    BattleType getBattleType() const { return battleType; }

    /**
     * @brief Kiểm tra xem player có thể chạy được không (chỉ wild được run).
     */
    bool canRun() const { return battleType == BattleType::WILD; }

    /**
     * @brief Lấy tổng số Pokemon ban đầu của player.
     */
    int getTotalPlayerMons() const { return totalPlayerMons; }

    /**
     * @brief Lấy tổng số Pokemon ban đầu của enemy.
     */
    int getTotalEnemyMons() const { return totalEnemyMons; }

    /**
     * @brief Hiển thị bag menu trong battle, xử lý item selection và use.
     *        GRADER: Sử dụng InventorySystem::forEach() để display items từ HashTable.
     * @param player Tham chiếu Player (lấy inventory)
     * @return True nếu item được dùng thành công (enemy sẽ counter-attack)
     *         False nếu bag rỗng, user cancel, hoặc item không applicable
     */
    bool showBag(Player &player);
};

#endif // BATTLESYSTEM_HPP
