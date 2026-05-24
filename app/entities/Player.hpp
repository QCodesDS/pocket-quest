#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Queue.hpp"
#include "Monster.hpp"
#include "../systems/InventorySystem.hpp"

/**
 * @struct Player
 * @brief  Cấu trúc dữ liệu lưu trữ thông tin và trạng thái của người chơi (Trainer).
 *         Quản lý party thông qua Queue<Monster> từ lib/ (Phase 03 lib usage).
 *         Quản lý bag thông qua InventorySystem với HashTable<string, Item> (Phase 04 lib usage).
 */
struct Player
{
    std::string name;        ///< Tên Trainer của người chơi
    int badges;              ///< Số lượng huy hiệu Gym đạt được (0 - 8)
    Queue<Monster> party;    ///< Đội hình chiến đấu dùng Queue<Monster> (FIFO: front mon battles first)
    std::string starterName; ///< Tên của Starter được chọn ban đầu

    // GRADER: InventorySystem uses HashTable<string, Item> from lib/ (Phase 04 lib usage)
    InventorySystem inventory; ///< Bag của player quản lý items

    /**
     * @brief Constructor khởi tạo Trainer mặc định với các giá trị rỗng.
     *        Khởi tạo inventory với Potion ×3 ban đầu.
     */
    Player();

    /**
     * @brief Khởi tạo party với Starter Pokémon dựa trên starterName.
     *        Được gọi sau khi IntroUI::showStarterSelect() cài đặt starterName.
     *        Sử dụng Queue<Monster> từ lib/ để lưu starter vào party.
     */
    void initializePartyWithStarter();
};

#endif // PLAYER_HPP
