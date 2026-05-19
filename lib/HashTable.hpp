/**
 * @file        HashTable.hpp
 * @brief       Triển khai lớp Bảng băm (Hash Table) tổng quát theo mô hình OOP.
 *
 * Cấu trúc dữ liệu này sử dụng phương pháp Separate Chaining để giải quyết xung đột băm.
 * Thay vì dùng danh sách liên kết truyền thống, mỗi Bucket được cấu trúc bằng một Cây AVL tự cân bằng.
 * Sự cải tiến này giúp giảm thiểu độ phức tạp thời gian trong trường hợp xấu nhất từ O(n) xuống O(log n)
 * cho các tác vụ chèn, xóa và tìm kiếm trên từng Bucket.
 */

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>

#include "AVL.hpp"

// ================================================================================
//  Pair Structure Definition
// ================================================================================

/**
 * @struct Pair
 * @brief  Cấu trúc lưu trữ cặp khóa - giá trị (Key - Value) làm phần tử cốt lõi trong Bucket.
 * @tparam K Kiểu dữ liệu của Khóa (Key).
 * @tparam V Kiểu dữ liệu của Giá trị (Value).
 */
template <typename K, typename V>
struct Pair {
    K key;    ///< Khóa định danh duy nhất của phần tử
    V value;  ///< Giá trị dữ liệu gắn liền với khóa

    /**
     * @brief Khởi tạo mặc định cho cấu trúc Pair.
     */
    Pair() = default;

    /**
     * @brief Khởi tạo Pair với đầy đủ thông tin khóa và giá trị.
     * @param k Khóa đầu vào
     * @param v Giá trị dữ liệu đầu vào
     */
    Pair(const K& k, const V& v) : key(k), value(v) {}

    /**
     * @brief Khởi tạo Pair chỉ với thông tin khóa, giá trị được khởi tạo mặc định.
     * @param k Khóa đầu vào
     */
    Pair(const K& k) : key(k), value(V{}) {}

    /**
     * @brief  Toán tử so sánh nhỏ hơn dựa trên Khóa (Key).
     * @return true nếu khóa của đối tượng này nhỏ hơn đối tượng o, ngược lại trả về false
     */
    bool operator<(const Pair& o) const { return key < o.key; }

    /**
     * @brief  Toán tử so sánh lớn hơn dựa trên Khóa (Key).
     * @return true nếu khóa của đối tượng này lớn hơn đối tượng o, ngược lại trả về false
     */
    bool operator>(const Pair& o) const { return key > o.key; }

    /**
     * @brief  Toán tử so sánh bằng nhau dựa trên Khóa (Key).
     * @return true nếu hai khóa hoàn toàn trùng nhau, ngược lại trả về false
     */
    bool operator==(const Pair& o) const { return key == o.key; }
};

// ================================================================================
//  HashTable Class Definition
// ================================================================================

/**
 * @class  HashTable
 * @brief  Lớp cấu trúc dữ liệu Bảng băm giải quyết xung đột bằng Separate Chaining (Cây AVL).
 * @tparam K Kiểu dữ liệu của Khóa (Key).
 * @tparam V Kiểu dữ liệu của Giá trị (Value).
 */
template <typename K, typename V>
class HashTable {
private:
    static const int DEFAULT_CAP = 64;  ///< Sức chứa mặc định ban đầu của mảng Buckets
    using Bucket = AVL<Pair<K, V>>;     ///< Định nghĩa kiểu dữ liệu Bucket là một Cây AVL chứa các cặp Pair

    Bucket* _buckets;  ///< Mảng động lưu trữ các Buckets (Cây AVL)
    int _cap;          ///< Tổng số lượng Buckets (Kích thước mảng băm)
    int _size;         ///< Tổng số lượng phần tử thực tế hiện có trong bảng băm

    // ================================================================================
    //  Private Internal Utilities (Hàm băm quá tải nội bộ cho các kiểu dữ liệu)
    // ================================================================================

    /**
     * @brief  Hàm băm quá tải cho kiểu dữ liệu chuỗi ký tự (std::string).
     * @note   Sử dụng thuật toán băm kinh điển DJB2 để giảm thiểu tối đa tỷ lệ trùng lặp.
     * @param  key Khóa dạng chuỗi ký tự cần băm
     * @return Chỉ số Bucket mục tiêu trong mảng băm (Giá trị nằm trong khoảng [0, _cap - 1])
     */
    int _hash(const std::string& key) const {
        unsigned long h = 5381;
        for (char c : key) h = h * 33 + (unsigned char)c;
        return (int)(h % (unsigned long)_cap);
    }

    /**
     * @brief  Hàm băm quá tải cho kiểu dữ liệu số nguyên (int).
     * @param  key Khóa dạng số nguyên cần băm
     * @return Chỉ số Bucket mục tiêu trong mảng băm
     */
    int _hash(int key) const { return (int)((unsigned int)key % (unsigned int)_cap); }

    /**
     * @brief  Hàm băm quá tải cho kiểu dữ liệu số nguyên lớn (long long).
     * @param  key Khóa dạng số nguyên lớn cần băm
     * @return Chỉ số Bucket mục tiêu trong mảng băm
     */
    int _hash(long long key) const { return (int)((unsigned long long)key % (unsigned long long)_cap); }

    /**
     * @brief  Hàm băm quá tải cho kiểu dữ liệu ký tự (char).
     * @param  key Khóa dạng ký tự cần băm
     * @return Chỉ số Bucket mục tiêu trong mảng băm
     */
    int _hash(char key) const { return (int)((unsigned char)key % (unsigned int)_cap); }

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một bảng băm mới với kích thước xác định.
     * @param cap Số lượng Buckets ban đầu được cấp phát (Mặc định là 64)
     */
    HashTable(int cap = DEFAULT_CAP) : _buckets(new Bucket[cap]), _cap(cap), _size(0) {}

    /**
     * @brief Hủy đối tượng bảng băm, giải phóng mảng Buckets và toàn bộ cấu trúc cây AVL nội bộ.
     */
    ~HashTable() { delete[] _buckets; }

    // ================================================================================
    //  Core Operations (Các thao tác cốt lõi trên Bảng băm)
    // ================================================================================

    /**
     * @brief  Chèn cặp (Khóa, Giá trị) vào bảng băm hoặc cập nhật giá trị nếu khóa đã tồn tại.
     * @note   Độ phức tạp thời gian: O(log n) trên một Bucket cụ thể trong trường hợp xấu nhất.
     * @param  key   Khóa định danh của phần tử cần chèn
     * @param  value Giá trị dữ liệu tương ứng của phần tử
     */
    void insert(const K& key, const V& value) {
        int idx = _hash(key);
        Pair<K, V> p(key, value);
        if (_buckets[idx].contains(p)) {
            _buckets[idx].remove(p);
        } else {
            _size++;
        }
        _buckets[idx].insert(p);
    }

    /**
     * @brief  Tìm kiếm và loại bỏ phần tử ra khỏi bảng băm dựa trên Khóa.
     * @note   Độ phức tạp thời gian: O(log n) trên một Bucket cụ thể trong trường hợp xấu nhất.
     * @param  key Khóa định danh của phần tử cần xóa bỏ
     * @return true nếu xóa thành công, false nếu khóa không tồn tại trong hệ thống
     */
    bool remove(const K& key) {
        int idx = _hash(key);
        Pair<K, V> p(key);
        if (!_buckets[idx].contains(p)) return false;
        _buckets[idx].remove(p);
        _size--;
        return true;
    }

    /**
     * @brief  Tìm kiếm và lấy ra con trỏ quản lý giá trị dựa trên Khóa cho trước.
     * @param  key Khóa định danh cần tra cứu dữ liệu
     * @return Con trỏ trỏ tới vùng dữ liệu Value nếu tìm thấy, ngược lại trả về nullptr
     */
    V* find(const K& key) {
        int idx = _hash(key);
        Pair<K, V> p(key);
        auto* node = _buckets[idx].search(p);
        return node ? &node->data.value : nullptr;
    }

    /**
     * @brief  Hàm hằng tìm kiếm và lấy ra con trỏ hằng quản lý giá trị dựa trên Khóa.
     * @param  key Khóa định danh cần tra cứu dữ liệu
     * @return Con trỏ hằng trỏ tới vùng dữ liệu Value nếu tìm thấy, ngược lại trả về nullptr
     */
    const V* find(const K& key) const {
        int idx = _hash(key);
        Pair<K, V> p(key);
        auto* node = _buckets[idx].search(p);
        return node ? &node->data.value : nullptr;
    }

    /**
     * @brief  Kiểm tra sự tồn tại của một Khóa trong bảng băm.
     * @param  key Khóa định danh cần kiểm tra sự hiện diện
     * @return true nếu khóa tồn tại trong bảng băm, ngược lại trả về false
     */
    bool contains(const K& key) const {
        int idx = _hash(key);
        Pair<K, V> p(key);
        return _buckets[idx].contains(p);
    }

    // ================================================================================
    //  Callback-driven Iteration (Hàm duyệt toàn bộ dữ liệu qua Callback)
    // ================================================================================

    /**
     * @brief  Duyệt qua toàn bộ các cặp khóa - giá trị hiện có trong bảng băm theo thứ tự tăng dần của khóa trên mỗi
     * Bucket.
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt (Function, Lambda, Functor)
     * @param  fn Hàm chức năng callback có chữ ký dạng `void(const K&, V&)` thực thi trên từng cặp phần tử
     */
    template <typename Fn>
    void forEach(Fn fn) {
        for (int i = 0; i < _cap; i++) {
            _buckets[i].inorder([&fn](const Pair<K, V>& p) { fn(p.key, const_cast<V&>(p.value)); });
        }
    }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Lấy tổng số lượng phần tử thực tế hiện đang quản lý trong bảng băm.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief  Kiểm tra xem cấu trúc bảng băm hiện tại có đang rỗng hay không.
     * @return true nếu bảng băm rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief Xóa sạch toàn bộ phần tử trong bảng băm, đưa số lượng về 0.
     * @note  Hàm này gọi lệnh `clear()` trên từng cây AVL để giải phóng bộ nhớ của các Node,
     *        nhưng giữ nguyên mảng lưu trữ gốc `_buckets` và kích thước `_cap`.
     */
    void clear() {
        for (int i = 0; i < _cap; i++) _buckets[i].clear();
        _size = 0;
    }
};

#endif  // HASHTABLE_HPP