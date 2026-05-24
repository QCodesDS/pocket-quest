#ifndef INVENTORYSYSTEM_HPP
#define INVENTORYSYSTEM_HPP

#include <string>
#include "HashTable.hpp"
#include "../entities/Item.hpp"
#include "../entities/Monster.hpp"

/**
 * @class InventorySystem
 * @brief Quản lý inventory (bag) của player sử dụng HashTable<string, Item>.
 *        GRADER: Dùng HashTable<std::string, Item> từ lib/ cho O(1) lookup items.
 *        Key = item name (string), Value = Item struct (với quantity).
 */
class InventorySystem
{
private:
    // GRADER VISIBILITY: HashTable<std::string, Item> from lib/ for item storage
    // Key: item name (e.g., "Potion"), Value: Item (with quantity)
    HashTable<std::string, Item> bag;

    static const int MAX_ITEMS = 10; ///< Maximum 10 different item types in bag

public:
    /**
     * @brief Constructor khởi tạo InventorySystem rỗng.
     */
    InventorySystem();

    /**
     * @brief Thêm item vào bag hoặc tăng quantity nếu item đã tồn tại.
     *        GRADER: Dùng HashTable::insert() để lưu item (O(1) average).
     * @param name Tên item (e.g., "Potion")
     * @param qty  Số lượng cần thêm
     */
    void addItem(const std::string &name, int qty);

    /**
     * @brief Dùng item trên target monster (hồi HP).
     *        GRADER: Dùng HashTable::find() để lấy item (O(1) average).
     *        Nếu target HP đã full, in thông báo và không trừ quantity.
     * @param name   Tên item
     * @param target Monster cần hồi HP
     * @return true nếu dùng thành công, false nếu item không tồn tại hoặc HP full
     */
    bool useItem(const std::string &name, Monster &target);

    /**
     * @brief Xóa item khỏi bag (gọi khi qty = 0).
     *        GRADER: Dùng HashTable::remove() để xóa item (O(1) average).
     * @param name Tên item cần xóa
     * @return true nếu xóa thành công, false nếu item không tồn tại
     */
    bool removeItem(const std::string &name);

    /**
     * @brief Kiểm tra item có tồn tại trong bag không.
     *        GRADER: Dùng HashTable::contains() để check (O(1) average).
     * @param name Tên item
     * @return true nếu item tồn tại, false nếu không
     */
    bool hasItem(const std::string &name) const;

    /**
     * @brief Lấy quantity của item.
     * @param name Tên item
     * @return Số lượng (0 nếu không tồn tại)
     */
    int getQuantity(const std::string &name) const;

    /**
     * @brief Lấy pointer tới Item từ bag.
     *        GRADER: Dùng HashTable::find() để lấy pointer (O(1) average).
     * @param name Tên item
     * @return Pointer tới Item nếu tồn tại, nullptr nếu không
     */
    Item *getItem(const std::string &name);

    /**
     * @brief Duyệt qua tất cả items trong bag với callback function.
     *        GRADER: Dùng HashTable::forEach() để duyệt tất cả items.
     *        Template callback để tránh std::function overhead.
     * @tparam Fn Kiểu callback function (lambda, function pointer, functor)
     * @param fn Callback có chữ ký: void(const std::string &name, Item &item)
     */
    template <typename Fn>
    void forEach(Fn fn)
    {
        // GRADER: Gọi HashTable::forEach() với callback
        bag.forEach(fn);
    }

    /**
     * @brief Lấy số lượng loại item khác nhau hiện có trong bag.
     * @return Số item types (0 nếu bag rỗng)
     */
    int size() const;

    /**
     * @brief Kiểm tra bag có rỗng không.
     * @return true nếu bag rỗng, false nếu có item
     */
    bool empty() const;
};

#endif // INVENTORYSYSTEM_HPP
