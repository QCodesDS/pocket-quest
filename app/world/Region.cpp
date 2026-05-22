#include "Region.hpp"
#include "../data/gen1_cities.hpp"

/**
 * @brief Nạp toàn bộ 10 thành phố từ mảng GEN1_CITIES vào LinkedList.
 *        Sử dụng City(const CityData&) constructor để khởi tạo từng City.
 */
void Region::load()
{
    cities.clear();
    // Duyệt qua 10 thành phố trong mảng GEN1_CITIES và chèn vào LinkedList
    for (int i = 0; i < GEN1_CITY_COUNT; ++i)
    {
        City newCity(GEN1_CITIES[i]);
        cities.insertBack(newCity);
    }
}

/**
 * @brief Đặt lại con trỏ về đầu danh sách (Pallet Town).
 */
void Region::resetCursor()
{
    cities.resetCursor();
}

/**
 * @brief Di chuyển con trỏ tới thành phố tiếp theo.
 *        @return True nếu di chuyển thành công, False nếu đã ở cuối danh sách.
 */
bool Region::moveNext()
{
    return cities.moveNext();
}

/**
 * @brief Kiểm tra xem con trỏ hiện tại có hợp lệ không.
 *        @return True nếu con trỏ chỉ tới một thành phố hợp lệ.
 */
bool Region::hasCurrent()
{
    return cities.hasCurrent();
}

/**
 * @brief Lấy tham chiếu đến thành phố mà con trỏ hiện đang chỉ.
 *        @return Tham chiếu City hiện tại.
 */
City &Region::getCurrent()
{
    return cities.getCurrent();
}
