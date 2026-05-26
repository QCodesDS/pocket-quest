#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include "Move.hpp"

/**
 * @struct Monster
 * @brief  Cấu trúc dữ liệu đại diện cho một Pokémon/Monster.
 *         Dùng trong Queue<Monster> để quản lý party chiến đấu (Phase 03 lib usage).
 *         Mỗi Monster có array 4 moves cho battle actions.
 */
struct Monster
{
    std::string name; ///< Tên của Monster (ví dụ: Charmander)
    std::string type; ///< Hệ của Monster (ví dụ: Fire)
    int id;           ///< Dex ID (1-151 Gen 1)
    int level;        ///< Level hiện tại (mặc định 5 wild, 15+ trainer/gym)
    int hp;           ///< HP hiện tại
    int maxHp;        ///< HP tối đa
    int atk;          ///< Điểm công (Attack)
    int def;          ///< Điểm thủ (Defense)
    int spd;          ///< Tốc độ (Speed)
    int spc;          ///< Chỉ số đặc biệt (Special — Gen 1: dùng cho cả Sp.Atk và Sp.Def)
    int exp;          ///< EXP hiện tại
    int nextLevelExp; ///< EXP cần để lên cấp tiếp theo
    Move moves[4];    ///< Array 4 moves của monster (cần dùng trong BattleSystem)

    /**
     * @brief Constructor khởi tạo Monster rỗng.
     */
    Monster();

    /**
     * @brief Constructor khởi tạo Monster đầy đủ thông tin.
     * @param n Tên monster
     * @param t Kiểu (type)
     * @param i Dex ID
     * @param lvl Level
     * @param hp_ HP tối đa
     * @param a Attack
     * @param d Defense
     * @param s Speed
     */
    Monster(const std::string &n, const std::string &t, int i, int lvl,
            int hp_, int a, int d, int s, int sp = -1);

    /**
     * @brief Thêm EXP cho Pokémon
     * @param amount Lượng EXP nhận được
     * @return true nếu thăng cấp
     */
    bool gainExp(int amount);

    /**
     * @brief Thực hiện việc tăng level và chỉ số
     */
    void levelUp();
};

#endif // MONSTER_HPP
