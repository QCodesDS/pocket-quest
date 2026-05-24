/**
 * @file  OverworldUI.hpp
 * @brief Giao diện Overworld: hiển thị thành phố hiện tại, NPC dialog, và các tùy chọn.
 */

#ifndef OVERWORLDUI_HPP
#define OVERWORLDUI_HPP

#include "../world/WorldMap.hpp"
#include "../entities/Player.hpp"
#include "../core/GameState.hpp"
#include "../core/Game.hpp"

/**
 * @namespace OverworldUI
 * @brief     Quản lý vòng lặp Overworld: render màn hình, xử lý input từ người chơi.
 */
namespace OverworldUI
{
    /**
     * @brief Chạy vòng lặp Overworld cho đến khi game kết thúc hoặc chuyển sang trạng thái khác.
     *        Hiển thị thành phố hiện tại, dialog NPC, và các tùy chọn di chuyển.
     * @param world Tham chiếu WorldMap để di chuyển qua các thành phố.
     * @param player Tham chiếu Player để cập nhật badges, party, v.v.
     * @param game Tham chiếu Game (reserved for future use).
     */
    void run(WorldMap &world, Player &player, Game &game);

    /**
     * @brief Hiển thị bag menu ngoài battle, xử lý item sử dụng trên pokemon.
     *        GRADER: Sử dụng InventorySystem::forEach() để duyệt HashTable items.
     * @param player Tham chiếu Player (inventory và party)
     */
    void handleBagMenu(Player &player);
}

#endif // OVERWORLDUI_HPP
