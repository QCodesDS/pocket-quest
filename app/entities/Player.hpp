#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Queue.hpp"
#include "Monster.hpp"

/**
 * @struct Player
 * @brief  Cấu trúc dữ liệu lưu trữ thông tin và trạng thái của người chơi (Trainer).
 */
struct Player {
    std::string name;               ///< Tên Trainer của người chơi
    int badges;                     ///< Số lượng huy hiệu Gym đạt được (0 - 8)
    Queue<Monster> party;           ///< Đội hình chiến đấu, phần tử ở đầu hàng ra trận trước (Queue FIFO)
    std::string starterName;        ///< Tên của Starter được chọn ban đầu

    /**
     * @brief Constructor khởi tạo Trainer mặc định với các giá trị rỗng.
     */
    Player();
};

#endif // PLAYER_HPP
