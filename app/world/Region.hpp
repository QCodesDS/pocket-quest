/**
 * @file  Region.hpp
 * @brief Quản lý danh sách 10 thành phố Kanto sử dụng LinkedList<City> từ lib/.
 *        Cung cấp giao diện con trỏ (cursor-based iteration) để duyệt qua các thành phố.
 */

#ifndef REGION_HPP
#define REGION_HPP

#include "City.hpp"
#include "../../lib/LinkedList.hpp"

/**
 * @struct Region
 * @brief  Quản lý một vùng miền (ví dụ: Kanto) với LinkedList<City> từ lib/LinkedList.hpp.
 *         Cung cấp cursor-based iteration để di chuyển qua các thành phố.
 *         Không dùng STL container — chỉ dùng LinkedList từ lib/.
 */
struct Region
{
    LinkedList<City> cities; ///< Danh sách 10 thành phố Kanto sử dụng LinkedList từ lib/

    /**
     * @brief Nạp toàn bộ 10 thành phố từ gen1_cities.hpp vào LinkedList.
     *        Gọi từ WorldMap::init().
     */
    void load();

    /**
     * @brief Đặt lại con trỏ (cursor) về đầu danh sách (Pallet Town).
     */
    void resetCursor();

    /**
     * @brief Di chuyển con trỏ tới thành phố tiếp theo.
     *        @return True nếu di chuyển thành công, False nếu đã ở cuối danh sách.
     */
    bool moveNext();

    /**
     * @brief Kiểm tra xem con trỏ hiện tại có hợp lệ không.
     *        @return True nếu con trỏ chỉ tới một thành phố hợp lệ.
     */
    bool hasCurrent();

    /**
     * @brief Lấy tham chiếu đến thành phố mà con trỏ hiện đang chỉ.
     *        @return Tham chiếu City hiện tại.
     */
    City &getCurrent();
};

#endif // REGION_HPP
