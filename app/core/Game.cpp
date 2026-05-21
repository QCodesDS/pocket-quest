#include "Game.hpp"
#include "../ui/UI.hpp"
#include "../ui/IntroUI.hpp"
#include "../ui/MenuUI.hpp"
#include <iostream>

Game::Game() : _state(GameState::MENU) {}

void Game::run() {
    bool running = true;
    while (running) {
        switch (_state) {
            case GameState::MENU:
                // 1. Màn hình Title screen chào mừng
                IntroUI::showTitleScreen();
                _state = GameState::INTRO;
                break;

            case GameState::INTRO:
                // 2. Chạy cốt truyện giới thiệu của Giáo sư Oak
                IntroUI::showOakDialog();
                // 3. Nhập tên nhân vật (có validate độ dài & rỗng)
                IntroUI::showNameInput(_player);
                // 4. Chọn Starter (có validate chữ/số ngoài phạm vi)
                IntroUI::showStarterSelect(_player);
                
                // Demo chuyển sang trạng thái WIN để test màn hình Victory
                _state = GameState::WIN;
                break;

            case GameState::WIN:
                // 5. Thử nghiệm giao diện chiến thắng (Victory Screen)
                MenuUI::showVictory(_player);
                // Demo chuyển tiếp sang GAMEOVER để test màn hình Thất bại
                _state = GameState::GAMEOVER;
                break;

            case GameState::GAMEOVER:
                // 6. Thử nghiệm giao diện thất bại (Game Over Screen)
                MenuUI::showGameOver(_player);
                // Hoàn tất chu trình demo Phase 01, thoát game
                running = false;
                break;

            default:
                running = false;
                break;
        }
    }
}

void Game::handleInput() {
    // Sẽ được mở rộng ở các phase sau khi tích hợp phím điều hướng bản đồ / chọn đòn đánh
}

void Game::update() {
    // Sẽ được mở rộng ở các phase sau khi xử lý chỉ số HP, lượt đấu, tiền vàng
}

void Game::render() {
    // Sẽ được mở rộng ở các phase sau để phân tách logic vẽ nâng cao
}
