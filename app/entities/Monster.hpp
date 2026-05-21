#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>

/**
 * @struct Monster
 * @brief  Cấu trúc dữ liệu đại diện cho một Pokémon/Monster (Placeholder phục vụ chèn vào Queue của Player).
 */
struct Monster {
    std::string name;   ///< Tên của Monster (ví dụ: Charmander)
    std::string type;   ///< Hệ của Monster (ví dụ: Fire)
    int hp;             ///< HP hiện tại
    int maxHp;          ///< HP tối đa
    int atk;            ///< Điểm công (Attack)
    int def;            ///< Điểm thủ (Defense)
    int spd;            ///< Tốc độ (Speed)
};

#endif // MONSTER_HPP
