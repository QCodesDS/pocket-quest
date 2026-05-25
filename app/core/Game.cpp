#include "Game.hpp"
#include "../ui/UI.hpp"
#include "../ui/IntroUI.hpp"
#include "../ui/MenuUI.hpp"
#include "../ui/OverworldUI.hpp"
#include "../data/gen1_trainers.hpp"
#include <iostream>

Game::Game() : _state(GameState::MENU), _currentBattleType(BattleType::WILD)
{
    // Khởi tạo bản đồ Kanto
    _world.init();
}

void Game::run()
{
    bool running = true;
    while (running)
    {
        switch (_state)
        {
        case GameState::MENU:
            // 1. Màn hình Title screen chào mừng
            IntroUI::showTitleScreen();
            _state = GameState::INTRO;
            break;

        case GameState::INTRO:
            // 1. Chạy cốt truyện game mở đầu pokemon
            // IntroUI::showOpeningStory();
            // 2. Chạy cốt truyện giới thiệu của Giáo sư Oak
            // IntroUI::showOakDialog();
            // 3. Nhập tên nhân vật (có validate độ dài & rỗng)
            IntroUI::showNameInput(_player);
            // 4. Chọn Starter (có validate chữ/số ngoài phạm vi)
            IntroUI::showStarterSelect(_player);
            // 5. Khởi tạo party với Starter - GRADER: Sử dụng Queue<Monster> từ lib/
            _player.initializePartyWithStarter();

            // Kích hoạt trận đấu Rival đầu game (Stage 0) ở Pallet Town
            {
                Trainer rival = Gen1Trainers::getRivalEncounter(0, _player.starterName);
                BattleSystem battle;
                battle.initializeTrainerBattle(_player, rival);

                UI::clearScreen();
                UI::printBox("Rival Battle", "Your rival Blue challenges you to a battle!");
                std::cout << "\nPress Enter to begin the first battle...";
                std::cin.ignore(10000, '\n');

                BattleResult rivalResult = battle.runBattle(_player);
                _player.party = battle.getPlayerParty();

                UI::clearScreen();
                if (rivalResult == BattleResult::WIN)
                {
                    UI::printBox("Victory!", "Prof. Oak: \"Ah! You won! That was an excellent battle!\"\nBlue: \"Humph! I'll catch a stronger Pokemon!\"");
                }
                else
                {
                    UI::printBox("Rival Battle", "Blue: \"Yeah! Am I great or what?\"\nProf. Oak: \"Don't worry, keep training your Pokemon!\"");
                    // Hồi phục HP cho Pokemon để không bị Game Over ngay từ đầu
                    if (!_player.party.empty())
                    {
                        _player.party.front().hp = _player.party.front().maxHp;
                    }
                }
                std::cout << "\nPress Enter to begin your journey...";
                std::cin.ignore(10000, '\n');
            }

            // Chuyển sang OVERWORLD để bắt đầu hành trình
            _state = GameState::OVERWORLD;
            break;

        case GameState::OVERWORLD:
            // 5. Chạy vòng lặp Overworld sử dụng LinkedList<City> từ WorldMap
            OverworldUI::run(_world, _player, *this);
            // Nếu OverworldUI đã set state sang WIN, giữ nguyên.
            if (_state == GameState::OVERWORLD)
            {
                _state = GameState::WIN;
            }
            break;

        case GameState::BATTLE:
            // 6. Chạy trận chiến (Wild hoặc Trainer) sử dụng BattleSystem với Queue/Stack từ lib/
            {
                BattleResult result = _battleSystem.runBattle(_player);

                if (result == BattleResult::WIN)
                {
                    // Victory: add gold, return to overworld
                    UI::clearScreen();
                    UI::printBox("Victory!", "You won the battle!");
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(10000, '\n');
                    _state = GameState::OVERWORLD;
                }
                else if (result == BattleResult::LOSS)
                {
                    // Defeat: game over
                    _state = GameState::GAMEOVER;
                }
                else if (result == BattleResult::RUN)
                {
                    // Escaped: return to overworld
                    _state = GameState::OVERWORLD;
                }
            }
            break;

        case GameState::WIN:
            // Victory has already been shown by the Pokemon League flow.
            running = false;
            break;

        case GameState::GAMEOVER:
            // 7. Thử nghiệm giao diện thất bại (Game Over Screen)
            MenuUI::showGameOver(_player);
            // Hoàn tất chu trình demo, thoát game
            running = false;
            break;

        default:
            running = false;
            break;
        }
    }
}

void Game::handleInput()
{
    // Sẽ được mở rộng ở các phase sau khi tích hợp phím điều hướng bản đồ / chọn đòn đánh
}

void Game::update()
{
    // Sẽ được mở rộng ở các phase sau khi xử lý chỉ số HP, lượt đấu, tiền vàng
}

void Game::render()
{
    // Sẽ được mở rộng ở các phase sau để phân tách logic vẽ nâng cao
}
