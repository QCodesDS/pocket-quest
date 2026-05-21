/**
 * @file  City.hpp
 * @brief Cấu trúc dữ liệu đại diện cho một địa điểm trong vùng Kanto.
 *        NPC dialog được lưu trong LinkedList<std::string> từ lib/ — không dùng STL.
 */

#ifndef CITY_HPP
#define CITY_HPP

#include <string>
#include "../../lib/LinkedList.hpp"

/**
 * @struct City
 * @brief  Một địa điểm trong thế giới game với tên, tag, dialog NPC và thông tin Gym.
 *         Trường npcDialog dùng LinkedList<std::string> từ lib/ để lưu các dòng hội thoại.
 */
struct City {
    std::string name;                     ///< Tên địa điểm (vd: "Cerulean City")
    std::string tag;                      ///< Nhãn hiển thị (vd: "GYM 2", "NO GYM", "HOMETOWN")
    LinkedList<std::string> npcDialog;    ///< Dòng hội thoại NPC — lib/LinkedList, không dùng std::vector
    bool hasGym;                          ///< True nếu địa điểm có Gym Leader
    std::string gymLeader;                ///< Tên Gym Leader (rỗng nếu không có Gym)

    /**
     * @brief Constructor mặc định.
     */
    City() : hasGym(false) {}

    /**
     * @brief Constructor đầy đủ tham số.
     */
    City(const std::string& n, const std::string& t,
         bool gym, const std::string& leader)
        : name(n), tag(t), hasGym(gym), gymLeader(leader) {}
};

#endif // CITY_HPP
