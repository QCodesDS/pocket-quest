#ifndef TYPE_SYSTEM_HPP
#define TYPE_SYSTEM_HPP

#include <string>

namespace TypeSystem
{
    /**
     * @brief Tính hệ số sức mạnh (Multiplier) dựa trên hệ của chiêu thức và Pokémon phòng thủ.
     *        Hỗ trợ song hệ bằng cách tách chuỗi defenderType (VD: "Poison/Flying").
     * 
     * @param attackType Hệ của chiêu thức (VD: "Water")
     * @param defenderType Hệ của Pokémon bị đánh (VD: "Grass/Poison" hoặc "Fire")
     * @return float Tỷ lệ sát thương (0.0, 0.25, 0.5, 1.0, 2.0, 4.0)
     */
    float getMultiplier(const std::string &attackType, const std::string &defenderType);

    /**
     * @brief Lấy hệ số điểm mạnh (STAB) khi Pokémon dùng chiêu cùng hệ.
     * 
     * @param attackType Hệ của chiêu thức.
     * @param attackerType Hệ của Pokémon (có thể là song hệ).
     * @return float 1.5 nếu trùng hệ, ngược lại 1.0.
     */
    float getSTAB(const std::string &attackType, const std::string &attackerType);
}

#endif // TYPE_SYSTEM_HPP
