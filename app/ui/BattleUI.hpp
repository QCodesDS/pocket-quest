#ifndef BATTLEUI_HPP
#define BATTLEUI_HPP

#include <string>
#include "../entities/Item.hpp"
#include "../systems/BattleSystem.hpp"
#include "../systems/InventorySystem.hpp"

/**
 * @namespace BattleUI
 * @brief     Quản lý giao diện hiển thị trận chiến (Battle Screen).
 *            Dùng UI utilities và Stack log từ BattleSystem.
 */
namespace BattleUI
{
    struct ItemEntry
    {
        std::string name;
        Item item;
    };
    /**
     * @brief Hiển thị màn hình chiến đấu chính (battle state).
     *        Bao gồm: Enemy info, Player info, Battle log (5 lines), Menu choices.
     *        GRADER: Hiển thị Stack<std::string> log với tối đa 5 dòng.
     * @param battle Tham chiếu BattleSystem (để lấy party, log)
     */
    void renderBattleScreen(BattleSystem &battle);

    /**
     * @brief Hiển thị danh sách 5 dòng log gần nhất từ Stack.
     *        GRADER: Dùng Stack<std::string> từ lib/ để lấy và display log.
     * @param log Tham chiếu Stack<std::string> từ BattleSystem
     */
    void displayLog(Stack<std::string> &log);

    /**
     * @brief Hiển thị bag menu với danh sách items từ InventorySystem.
     *        GRADER: Sắp xếp items theo tên bằng insertionSort trước khi hiển thị.
     * @param inventory Tham chiếu InventorySystem của player
     * @param items Mảng item entries đã được thu thập
     * @param count Số lượng item entries trong mảng
     */
    void displayBagMenu(InventorySystem &inventory, ItemEntry items[], int &count);
}

#endif // BATTLEUI_HPP
