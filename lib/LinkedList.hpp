/**
 * @file        LinkedList.hpp
 * @brief       Triển khai lớp Danh sách liên kết đơn (Singly Linked List) tổng quát theo mô hình OOP.
 *
 * Lớp cấu trúc dữ liệu này đóng gói toàn bộ các thuộc tính quản lý liên kết Node vào vùng
 * bảo mật thuộc tính riêng tư (private), ngăn chặn việc truy cập trực tiếp vào con trỏ hệ thống.
 * Đồng thời, lớp cung cấp giao diện lập trình hướng đối tượng (public) an toàn, tích hợp cơ chế
 * con trỏ tuần tự (Cursor) và bộ duyệt Callback Lambda tối ưu.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

/**
 * @class  LinkedList
 * @brief  Lớp cấu trúc dữ liệu Danh sách liên kết đơn (Singly Linked List).
 * @tparam T Kiểu dữ liệu của các phần tử được lưu trữ trong danh sách.
 */
template <typename T>
class LinkedList {
private:
    /**
     * @struct LLNode
     * @brief  Cấu trúc một phần tử Node nội bộ (Nested Struct) phục vụ việc liên kết dữ liệu.
     */
    struct LLNode {
        T data;        ///< Dữ liệu của phần tử
        LLNode* next;  ///< Con trỏ quản lý liên kết đến Node kế tiếp

        /**
         * @brief Khởi tạo một Node mới với dữ liệu cho trước.
         * @param val Giá trị dữ liệu cần lưu trữ
         */
        LLNode(const T& val) : data(val), next(nullptr) {}
    };

    LLNode* _head;    ///< Con trỏ quản lý Node đầu danh sách
    LLNode* _tail;    ///< Con trỏ quản lý Node cuối danh sách
    LLNode* _cursor;  ///< Con trỏ nội bộ phục vụ tác vụ duyệt tuần tự
    int _size;        ///< Số lượng phần tử hiện có trong danh sách

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một đối tượng danh sách liên kết đơn rỗng.
     */
    LinkedList() : _head(nullptr), _tail(nullptr), _cursor(nullptr), _size(0) {}

    /**
     * @brief Hủy đối tượng danh sách, tự động thu hồi toàn bộ vùng nhớ động của các Node.
     */
    ~LinkedList() { clear(); }

    // ================================================================================
    //  Mutation Operations (Thao tác Thêm / Xóa phần tử)
    // ================================================================================

    /**
     * @brief  Thêm một phần tử vào ngay đầu danh sách.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @param  val Giá trị phần tử cần chèn
     */
    void insertFront(const T& val) {
        LLNode* node = new LLNode(val);
        node->next = _head;
        _head = node;
        if (!_tail) _tail = _head;
        if (!_cursor) _cursor = _head;
        _size++;
    }

    /**
     * @brief  Thêm một phần tử vào cuối danh sách.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @param  val Giá trị phần tử cần chèn
     */
    void insertBack(const T& val) {
        LLNode* node = new LLNode(val);
        if (!_tail) {
            _head = _tail = node;
        } else {
            _tail->next = node;
            _tail = node;
        }
        if (!_cursor) _cursor = _head;
        _size++;
    }

    /**
     * @brief  Chèn một phần tử vào vị trí chỉ định (0-based Index).
     * @note   Độ phức tạp thời gian thuật toán: O(n).
     *         Nếu index <= 0, tự động chèn vào đầu; nếu index >= size, tự động chèn vào cuối.
     * @param  index Vị trí cần chèn trong danh sách
     * @param  val Giá trị phần tử cần chèn
     */
    void insertAt(int index, const T& val) {
        if (index <= 0) {
            insertFront(val);
            return;
        }
        if (index >= _size) {
            insertBack(val);
            return;
        }
        LLNode* prev = _head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        LLNode* node = new LLNode(val);
        node->next = prev->next;
        prev->next = node;
        _size++;
    }

    /**
     * @brief  Tìm và xóa phần tử đầu tiên có giá trị trùng khớp với val.
     * @note   Độ phức tạp thời gian thuật toán: O(n).
     * @param  val Giá trị dữ liệu của phần tử cần xóa
     * @return true nếu tìm thấy và xóa thành công, ngược lại trả về false
     */
    bool remove(const T& val) {
        LLNode* prev = nullptr;
        LLNode* cur = _head;
        while (cur) {
            if (cur->data == val) {
                if (cur == _cursor) _cursor = cur->next ? cur->next : _head;
                if (prev)
                    prev->next = cur->next;
                else
                    _head = cur->next;
                if (cur == _tail) _tail = prev;
                delete cur;
                _size--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    /**
     * @brief  Xóa một phần tử tại vị trí chỉ định (0-based Index).
     * @note   Độ phức tạp thời gian thuật toán: O(n).
     * @param  index Vị trí phần tử cần xóa
     * @return true nếu vị trí hợp lệ và xóa thành công, ngược lại trả về false
     */
    bool removeAt(int index) {
        if (index < 0 || index >= _size) return false;
        LLNode* prev = nullptr;
        LLNode* cur = _head;
        for (int i = 0; i < index; i++) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == _cursor) _cursor = cur->next ? cur->next : _head;
        if (prev)
            prev->next = cur->next;
        else
            _head = cur->next;
        if (cur == _tail) _tail = prev;
        delete cur;
        _size--;
        return true;
    }

    // ================================================================================
    //  Query Operations (Thao tác Tra cứu / Truy xuất dữ liệu)
    // ================================================================================

    /**
     * @brief  Tìm kiếm node đầu tiên lưu trữ giá trị val.
     * @note   Độ phức tạp thời gian thuật toán: O(n). Phương thức hằng (const).
     * @param  val Giá trị cần tìm kiếm
     * @return Con trỏ LLNode chứa dữ liệu nếu tìm thấy, ngược lại trả về nullptr
     */
    LLNode* find(const T& val) const {
        LLNode* cur = _head;
        while (cur) {
            if (cur->data == val) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    /**
     * @brief  Truy xuất tham chiếu dữ liệu của phần tử tại vị trí index chỉ định.
     * @note   Độ phức tạp thời gian thuật toán: O(n). Không kiểm tra biên an toàn.
     * @param  index Vị trí phần tử cần lấy (0-based)
     * @return Tham chiếu (Reference) tới dữ liệu phần tử bên trong node
     */
    T& at(int index) {
        LLNode* cur = _head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->data;
    }

    /**
     * @brief  Truy xuất tham chiếu hằng dữ liệu của phần tử tại vị trí index chỉ định.
     * @note   Độ phức tạp thời gian thuật toán: O(n). Phiên bản dành cho đối tượng hằng (const).
     * @param  index Vị trí phần tử cần lấy (0-based)
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu phần tử
     */
    const T& at(int index) const {
        LLNode* cur = _head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->data;
    }

    // ================================================================================
    //  Cursor-based Iteration (Cơ chế duyệt tuần tự bằng con trỏ Cursor)
    // ================================================================================

    /**
     * @brief Đặt lại vị trí của con trỏ trượt nội bộ (Cursor) về đầu danh sách.
     */
    void resetCursor() { _cursor = _head; }

    /**
     * @brief  Dịch chuyển con trỏ trượt nội bộ (Cursor) sang Node kế tiếp.
     * @return true nếu dịch chuyển thành công, false nếu Cursor đang ở cuối danh sách
     */
    bool moveNext() {
        if (_cursor && _cursor->next) {
            _cursor = _cursor->next;
            return true;
        }
        return false;
    }

    /**
     * @brief  Kiểm tra xem phía sau vị trí Cursor hiện tại có còn phần tử nào khác không.
     * @return true nếu còn phần tử kế tiếp, ngược lại trả về false
     */
    bool hasNext() const { return _cursor && _cursor->next; }

    /**
     * @brief  Kiểm tra xem trạng thái con trỏ Cursor hiện tại có hợp lệ (khác nullptr) hay không.
     * @return true nếu hợp lệ, ngược lại trả về false
     */
    bool hasCurrent() const { return _cursor != nullptr; }

    /**
     * @brief  Lấy tham chiếu dữ liệu tại vị trí con trỏ Cursor đang đứng.
     * @return Tham chiếu tới dữ liệu phần tử hiện tại
     */
    T& getCurrent() { return _cursor->data; }

    // ================================================================================
    //  Callback-driven Traversal (Duyệt cấu trúc dữ liệu qua Callback Lambda)
    // ================================================================================

    /**
     * @brief  Duyệt tuần tự từ đầu đến cuối danh sách và thực thi một hàm chức năng (Callable).
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` hoặc `void(T&)`
     */
    template <typename Fn>
    void traverseForward(Fn fn) const {
        LLNode* cur = _head;
        while (cur) {
            fn(cur->data);
            cur = cur->next;
        }
    }

    /**
     * @brief  Duyệt ngược từ cuối về đầu danh sách và thực thi một hàm chức năng (Callable).
     * @note   Phương thức cấp phát một mảng tạm thời để lưu trữ dữ liệu nhằm hỗ trợ duyệt ngược trên
     *         danh sách liên kết đơn, tự động giải phóng bộ nhớ sau khi hoàn tất.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void traverseReverse(Fn fn) const {
        if (!_head) return;
        T* arr = new T[_size];
        LLNode* cur = _head;
        for (int i = 0; i < _size; i++) {
            arr[i] = cur->data;
            cur = cur->next;
        }
        for (int i = _size - 1; i >= 0; i--) fn(arr[i]);
        delete[] arr;
    }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Lấy số lượng phần tử hiện tại có trong danh sách liên kết.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief  Kiểm tra danh sách liên kết hiện tại có đang rỗng hay không.
     * @return true nếu danh sách rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief Xóa toàn bộ nội dung của danh sách, giải phóng mọi phân vùng bộ nhớ động đã cấp phát.
     */
    void clear() {
        LLNode* cur = _head;
        while (cur) {
            LLNode* tmp = cur->next;
            delete cur;
            cur = tmp;
        }
        _head = _tail = _cursor = nullptr;
        _size = 0;
    }
};

#endif  // LINKEDLIST_HPP