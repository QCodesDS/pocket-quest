#ifndef BATTLEUI_HPP
#define BATTLEUI_HPP

#include <string>
#include "../systems/BattleSystem.hpp"

/**
 * @namespace BattleUI
 * @brief     Quản lý giao diện hiển thị trận chiến (Battle Screen).
 *            Dùng UI utilities và Stack log từ BattleSystem.
 */
namespace BattleUI
{
    /**
     * @brief Hiển thị màn hình chiến đấu chính (battle state).
     *        Bao gồm: Enemy info, Player info, Battle log (5 lines), Menu choices.
     *        GRADER: Hiển thị Stack<std::string> log với tối đa 5 dòng.
     * @param battle Tham chiếu BattleSystem (để lấy party, log)
     */
    void renderBattleScreen(BattleSystem &battle);

    /**
     * @brief Hiển thị thông tin Pokémon (tên, level, HP bar).
     * @param mon Tham chiếu Monster
     * @param owner Tên owner ("Enemy" hoặc "Your")
     * @param isEnemy True nếu là enemy mon, False nếu là player mon
     */
    void displayMonsterInfo(Monster &mon, const std::string &owner, bool isEnemy);

    /**
     * @brief Hiển thị danh sách 5 dòng log gần nhất từ Stack.
     *        GRADER: Dùng Stack<std::string> từ lib/ để lấy và display log.
     * @param log Tham chiếu Stack<std::string> từ BattleSystem
     */
    void displayLog(Stack<std::string> &log);

    /**
     * @brief Hiển thị menu tùy chọn chiến đấu ([1] Fight, [2] Bag, [3] Switch, [4] Run).
     */
    void displayActionMenu();
}

#endif // BATTLEUI_HPP
