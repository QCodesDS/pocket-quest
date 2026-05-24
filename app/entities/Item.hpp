#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

/**
 * @struct Item
 * @brief  Cấu trúc dữ liệu đại diện cho một Item trong game.
 *         Dùng với HashTable<std::string, Item> để quản lý inventory (Phase 04 lib usage).
 *         Item là plain data struct không có method phức tạp.
 */
struct Item
{
    std::string name; ///< Tên item (ví dụ: "Potion", "Super Potion")
    int healAmount;   ///< Số HP được hồi phục khi dùng item
    int quantity;     ///< Số lượng item hiện có trong bag

    /**
     * @brief Constructor khởi tạo Item rỗng (default: empty/zero values).
     */
    Item();

    /**
     * @brief Constructor khởi tạo Item với đầy đủ thông tin.
     * @param n Tên item
     * @param heal Số HP được hồi phục
     * @param qty Số lượng ban đầu
     */
    Item(const std::string &n, int heal, int qty);
};

// ============================================================================
// Inline Constructor Implementations
// ============================================================================

inline Item::Item() : name(""), healAmount(0), quantity(0) {}

inline Item::Item(const std::string &n, int heal, int qty)
    : name(n), healAmount(heal), quantity(qty) {}

#endif // ITEM_HPP
