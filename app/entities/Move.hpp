#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

/**
 * @struct Move
 * @brief  Cấu trúc dữ liệu đại diện cho một Pokémon move (đòn đánh).
 *         Dùng trong Monster.moves[] để lưu trữ bộ kỹ năng của từng monster.
 */
struct Move
{
    std::string name; ///< Tên của move (ví dụ: Ember, Gust, Scratch)
    std::string type; ///< Hệ của chiêu thức (ví dụ: Fire, Water, Normal)
    int power;        ///< Sức mạnh move, dùng cho công thức damage = (power * atk) / def
    int pp;           ///< Power Point hiện tại (số lần còn có thể dùng)
    int maxPp;        ///< Power Point tối đa

    /**
     * @brief Constructor khởi tạo Move với các tham số.
     * @param n Tên move
     * @param t Hệ chiêu thức
     * @param p Sức mạnh (power)
     * @param maxP Power Point tối đa
     */
    Move(const std::string &n = "", const std::string &t = "Normal", int p = 0, int maxP = 20)
        : name(n), type(t), power(p), pp(maxP), maxPp(maxP) {}
};

#endif // MOVE_HPP
