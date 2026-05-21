#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"
#include "../entities/Player.hpp"

/**
 * @class Game
 * @brief Lớp điều phối vòng lặp game chính (Main Game Loop) và quản lý chuyển đổi trạng thái.
 */
class Game {
private:
    GameState _state;       ///< Trạng thái hiện tại của game
    Player _player;         ///< Thông tin và trạng thái người chơi

    /**
     * @brief Xử lý nhập liệu từ bàn phím tương ứng với trạng thái hiện tại.
     */
    void handleInput();

    /**
     * @brief Cập nhật logic game dựa trên dữ liệu mới nhận được.
     */
    void update();

    /**
     * @brief Thực hiện vẽ/kẻ vẽ giao diện tương ứng với trạng thái hiện tại.
     */
    void render();

public:
    /**
     * @brief Khởi tạo đối tượng Game mới, đặt trạng thái ban đầu là MENU.
     */
    Game();

    /**
     * @brief Vòng lặp game chính chạy liên tục cho đến khi trò chơi kết thúc.
     */
    void run();

    /**
     * @brief Lấy trạng thái hiện tại của game.
     * @return Trạng thái GameState hiện thời
     */
    GameState getState() const { return _state; }

    /**
     * @brief Thiết lập trạng thái mới cho game.
     * @param state Trạng thái GameState mong muốn chuyển đổi
     */
    void setState(GameState state) { _state = state; }
};

#endif // GAME_HPP
