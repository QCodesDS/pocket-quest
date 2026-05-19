/**
 * @file        Stack.hpp
 * @brief       Triển khai lớp Ngăn xếp LIFO (Last-In, First-Out) tổng quát theo mô hình OOP.
 *
 * Lớp cấu trúc dữ liệu này đóng gói toàn bộ các thuộc tính quản lý liên kết Node vào vùng
 * bảo mật thuộc tính riêng tư (private), cung cấp giao diện lập trình hướng đối tượng (public)
 * an toàn, tối ưu hiệu năng cho các tác vụ với độ phức tạp hằng số O(1).
 */

#ifndef STACK_HPP
#define STACK_HPP

/**
 * @class  Stack
 * @brief  Lớp cấu trúc dữ liệu Ngăn xếp (Stack) hoạt động theo nguyên lý LIFO.
 * @tparam T Kiểu dữ liệu của các phần tử được lưu trữ trong ngăn xếp.
 */
template <typename T>
class Stack {
private:
    /**
     * @struct SNode
     * @brief  Cấu trúc một phần tử Node nội bộ (Nested Struct) phục vụ việc liên kết dữ liệu.
     */
    struct SNode {
        T data;       ///< Dữ liệu của phần tử
        SNode* next;  ///< Con trỏ liên kết đến Node tiếp theo phía dưới trong ngăn xếp

        /**
         * @brief Khởi tạo một Node ngăn xếp mới với dữ liệu cho trước.
         * @param val Giá trị dữ liệu cần lưu trữ
         */
        SNode(const T& val) : data(val), next(nullptr) {}
    };

    SNode* _top;  ///< Con trỏ quản lý phần tử ở đỉnh ngăn xếp (Top element)
    int _size;    ///< Số lượng phần tử hiện có trong ngăn xếp

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một đối tượng ngăn xếp rỗng.
     */
    Stack() : _top(nullptr), _size(0) {}

    /**
     * @brief Hủy đối tượng ngăn xếp, tự động thu hồi toàn bộ vùng nhớ động của các Node.
     */
    ~Stack() { clear(); }

    // ================================================================================
    //  Core Stack Operations (Các thao tác cốt lõi trên Ngăn xếp)
    // ================================================================================

    /**
     * @brief  Thêm (đẩy) một phần tử mới vào đỉnh ngăn xếp.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @param  val Giá trị phần tử cần đưa vào ngăn xếp
     */
    void push(const T& val) {
        SNode* node = new SNode(val);
        node->next = _top;
        _top = node;
        _size++;
    }

    /**
     * @brief  Lấy và loại bỏ phần tử nằm ở đỉnh ngăn xếp.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này nhằm tránh lỗi sập hệ thống
     * (Undefined Behavior).
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Giá trị của phần tử vừa bị loại bỏ ở đỉnh ngăn xếp
     */
    T pop() {
        T val = _top->data;
        SNode* tmp = _top;
        _top = _top->next;
        delete tmp;
        _size--;
        return val;
    }

    /**
     * @brief  Truy xuất tham chiếu đến phần tử nằm ở đỉnh ngăn xếp mà không loại bỏ nó.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Tham chiếu (Reference) tới dữ liệu phần tử đỉnh hiện tại
     */
    T& top() { return _top->data; }

    /**
     * @brief  Truy xuất tham chiếu hằng đến phần tử nằm ở đỉnh ngăn xếp mà không loại bỏ nó.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này. Phiên bản dành cho đối tượng
     * hằng (const).
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu phần tử đỉnh hiện tại
     */
    const T& top() const { return _top->data; }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Kiểm tra xem ngăn xếp hiện tại có đang rỗng hay không.
     * @return true nếu ngăn xếp rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief  Lấy số lượng phần tử hiện tại có trong ngăn xếp.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief Xóa toàn bộ nội dung của ngăn xếp, giải phóng mọi phân vùng bộ nhớ động đã cấp phát.
     */
    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

#endif  // STACK_HPP