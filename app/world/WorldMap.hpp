/**
 * @file  WorldMap.hpp
 * @brief Quản lý toàn bộ bản đồ thế giới (Kanto) sử dụng Region.
 *        Cung cấp giao diện để di chuyển qua các thành phố và truy vấn trạng thái.
 */

#ifndef WORLDMAP_HPP
#define WORLDMAP_HPP

#include "Region.hpp"

/**
 * @struct WorldMap
 * @brief  Quản lý toàn bộ thế giới game (hiện tại chỉ Kanto region).
 *         Gói (wrap) Region để cung cấp giao diện cao cấp cho movement/queries.
 */
struct WorldMap
{
    Region kanto; ///< Vùng Kanto với 10 thành phố

    /**
     * @brief Khởi tạo bản đồ: nạp dữ liệu Kanto từ gen1_cities.hpp.
     */
    void init();

    /**
     * @brief Đặt lại con trỏ về Pallet Town (thành phố đầu tiên).
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

    /**
     * @brief Kiểm tra xem thành phố hiện tại có phải Indigo Plateau không.
     *        @return True nếu thành phố hiện tại tên là "Indigo Plateau".
     */
    bool atIndigoPlateau();
};

#endif // WORLDMAP_HPP
