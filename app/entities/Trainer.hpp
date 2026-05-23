#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <string>
#include "Queue.hpp"
#include "Monster.hpp"

/**
 * @enum TrainerType
 * @brief Loại nhân vật huấn luyện (Gym leader, Elite Four, Champion, v.v.)
 */
enum class TrainerType
{
    GYM,      ///< Gym leader
    ELITE,    ///< Elite Four member
    CHAMPION, ///< Champion
    WILD      ///< Trainer gặp đường (stub)
};

/**
 * @struct Trainer
 * @brief  Cấu trúc dữ liệu đại diện cho một Trainer/Gym Leader.
 *         Quản lý party thông qua Queue<Monster> từ lib/ (FIFO: front mon battles first).
 */
struct Trainer
{
    std::string name;     ///< Tên Trainer (ví dụ: Brock, Misty)
    TrainerType type;     ///< Loại trainer (GYM, ELITE, CHAMPION)
    Queue<Monster> party; ///< Đội hình Pokémon dùng Queue<Monster> (FIFO)
    int level;            ///< Level trung bình của mons
    std::string city;     ///< Thành phố nơi trainer ở (nếu là Gym leader)

    /**
     * @brief Constructor khởi tạo Trainer mặc định.
     */
    Trainer();

    /**
     * @brief Constructor khởi tạo Trainer với thông tin cụ thể.
     * @param n Tên trainer
     * @param t Loại trainer
     * @param lvl Level trung bình
     * @param c Thành phố
     */
    Trainer(const std::string &n, TrainerType t, int lvl, const std::string &c = "");
};

#endif // TRAINER_HPP
