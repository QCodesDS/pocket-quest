#include "Game.hpp"
#include "../ui/UI.hpp"
#include "../ui/IntroUI.hpp"
#include "../ui/MenuUI.hpp"
#include "../ui/OverworldUI.hpp"
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

            // Chuyển sang OVERWORLD để bắt đầu hành trình
            _state = GameState::OVERWORLD;
            break;

        case GameState::OVERWORLD:
            // 5. Chạy vòng lặp Overworld sử dụng LinkedList<City> từ WorldMap
            OverworldUI::run(_world, _player, *this);
            // TODO: Sau khi kết thúc Overworld, chuyển sang trạng thái tiếp theo
            // Hiện tại: test demo = chuyển sang WIN
            _state = GameState::WIN;
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
            // 6. Thử nghiệm giao diện chiến thắng (Victory Screen)
            MenuUI::showVictory(_player);
            // Demo chuyển tiếp sang GAMEOVER để test màn hình Thất bại
            _state = GameState::GAMEOVER;
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
