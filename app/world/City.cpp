#include "City.hpp"
#include "../data/gen1_cities.hpp"

/**
 * @brief Constructor nạp dữ liệu từ CityData (POD struct).
 *        Sử dụng LinkedList<std::string> từ lib/ để lưu NPC dialog — không dùng STL.
 */
City::City(const CityData &data)
    : name(data.name), tag(data.tag), hasGym(data.hasGym), gymLeader(data.gymLeader ? data.gymLeader : "")
{
    // Nạp 2 dòng NPC dialog vào LinkedList
    for (int i = 0; i < 2; ++i)
    {
        if (data.npcDialog[i])
        {
            npcDialog.insertBack(std::string(data.npcDialog[i]));
        }
    }
}
