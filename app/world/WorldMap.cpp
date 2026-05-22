#include "WorldMap.hpp"

/**
 * @brief Khởi tạo bản đồ: nạp dữ liệu Kanto từ gen1_cities.hpp.
 */
void WorldMap::init()
{
    kanto.load();
    kanto.resetCursor();
}

/**
 * @brief Đặt lại con trỏ về Pallet Town (thành phố đầu tiên).
 */
void WorldMap::resetCursor()
{
    kanto.resetCursor();
}

/**
 * @brief Di chuyển con trỏ tới thành phố tiếp theo.
 *        @return True nếu di chuyển thành công, False nếu đã ở cuối danh sách.
 */
bool WorldMap::moveNext()
{
    return kanto.moveNext();
}

/**
 * @brief Kiểm tra xem con trỏ hiện tại có hợp lệ không.
 *        @return True nếu con trỏ chỉ tới một thành phố hợp lệ.
 */
bool WorldMap::hasCurrent()
{
    return kanto.hasCurrent();
}

/**
 * @brief Lấy tham chiếu đến thành phố mà con trỏ hiện đang chỉ.
 *        @return Tham chiếu City hiện tại.
 */
City &WorldMap::getCurrent()
{
    return kanto.getCurrent();
}

/**
 * @brief Kiểm tra xem thành phố hiện tại có phải Indigo Plateau không.
 *        @return True nếu thành phố hiện tại tên là "Indigo Plateau".
 */
bool WorldMap::atIndigoPlateau()
{
    if (!hasCurrent())
        return false;
    return getCurrent().name == "Indigo Plateau";
}
