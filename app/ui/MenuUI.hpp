#ifndef MENUUI_HPP
#define MENUUI_HPP

#include "../entities/Player.hpp"

/**
 * @namespace MenuUI
 * @brief     Quản lý các màn hình kết thúc game bao gồm Game Over và Victory.
 */
namespace MenuUI {
    /**
     * @brief Hiển thị màn hình Game Over hiển thị thống kê lượt chơi.
     * @param player Tham chiếu đối tượng Player để lấy stats
     */
    void showGameOver(const Player& player);

    /**
     * @brief Hiển thị màn hình chiến thắng Champion.
     * @param player Tham chiếu đối tượng Player để lấy thông tin vinh danh
     */
    void showVictory(const Player& player);
}

#endif // MENUUI_HPP
