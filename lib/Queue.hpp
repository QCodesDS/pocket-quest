/**
 * @file        Queue.hpp
 * @brief       Triển khai lớp Hàng đợi FIFO (First-In, First-Out) tổng quát theo mô hình OOP.
 *
 * Lớp cấu trúc dữ liệu này đóng gói toàn bộ các thuộc tính quản lý liên kết Node vào vùng
 * bảo mật thuộc tính riêng tư (private), cung cấp giao diện lập trình hướng đối tượng (public)
 * an toàn, tối ưu hóa hiệu năng cho các tác vụ thêm ở cuối và xóa ở đầu đạt độ phức tạp hằng số O(1).
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

/**
 * @class  Queue
 * @brief  Lớp cấu trúc dữ liệu Hàng đợi (Queue) hoạt động theo nguyên lý FIFO.
 * @tparam T Kiểu dữ liệu của các phần tử được lưu trữ trong hàng đợi.
 */
template <typename T>
class Queue
{
private:
    /**
     * @struct QNode
     * @brief  Cấu trúc một phần tử Node nội bộ (Nested Struct) phục vụ việc liên kết dữ liệu.
     */
    struct QNode
    {
        T data;      ///< Dữ liệu của phần tử
        QNode *next; ///< Con trỏ liên kết đến Node tiếp theo phía sau trong hàng đợi

        /**
         * @brief Khởi tạo một Node hàng đợi mới với dữ liệu cho trước.
         * @param val Giá trị dữ liệu cần lưu trữ
         */
        QNode(const T &val) : data(val), next(nullptr) {}
    };

    QNode *_front; ///< Con trỏ quản lý phần tử ở đầu hàng đợi (Vị trí lấy dữ liệu ra)
    QNode *_back;  ///< Con trỏ quản lý phần tử ở cuối hàng đợi (Vị trí thêm dữ liệu vào)
    int _size;     ///< Số lượng phần tử hiện có trong hàng đợi

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một đối tượng hàng đợi rỗng.
     */
    Queue() : _front(nullptr), _back(nullptr), _size(0) {}

    /**
     * @brief Hủy đối tượng hàng đợi, tự động thu hồi toàn bộ vùng nhớ động của các Node.
     */
    ~Queue() { clear(); }

    // ================================================================================
    //  Core Queue Operations (Các thao tác cốt lõi trên Hàng đợi)
    // ================================================================================

    /**
     * @brief  Thêm một phần tử mới vào cuối hàng đợi (Enqueue).
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @param  val Giá trị phần tử cần đưa vào hàng đợi
     */
    void enqueue(const T &val)
    {
        QNode *node = new QNode(val);
        if (!_back)
        {
            _front = _back = node;
        }
        else
        {
            _back->next = node;
            _back = node;
        }
        _size++;
    }

    /**
     * @brief  Lấy và loại bỏ phần tử nằm ở đầu hàng đợi (Dequeue).
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này nhằm tránh lỗi sập hệ thống
     * (Undefined Behavior).
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Giá trị của phần tử vừa bị loại bỏ ở đầu hàng đợi
     */
    T dequeue()
    {
        T val = _front->data;
        QNode *tmp = _front;
        _front = _front->next;
        if (!_front)
            _back = nullptr;
        delete tmp;
        _size--;
        return val;
    }

    /**
     * @brief  Truy xuất tham chiếu đến phần tử nằm ở đầu hàng đợi mà không loại bỏ nó.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Tham chiếu (Reference) tới dữ liệu phần tử đầu hàng hiện tại
     */
    T &front() { return _front->data; }

    /**
     * @brief  Truy xuất tham chiếu hằng đến phần tử nằm ở đầu hàng đợi mà không loại bỏ nó.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này. Phiên bản dành cho đối tượng
     * hằng (const).
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu phần tử đầu hàng hiện tại
     */
    const T &front() const { return _front->data; }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Kiểm tra xem hàng đợi hiện tại có đang rỗng hay không.
     * @return true nếu hàng đợi rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief  Lấy số lượng phần tử hiện tại có trong hàng đợi.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief Xóa toàn bộ nội dung của hàng đợi, giải phóng mọi phân vùng bộ nhớ động đã cấp phát.
     */
    void clear()
    {
        while (!empty())
        {
            dequeue();
        }
    }

    // ================================================================================
    //  Copy Support
    // ================================================================================

    /**
     * @brief Copy constructor deep-copies queue contents.
     */
    Queue(const Queue &other) : _front(nullptr), _back(nullptr), _size(0)
    {
        QNode *cur = other._front;
        while (cur)
        {
            enqueue(cur->data);
            cur = cur->next;
        }
    }

    /**
     * @brief Copy assignment operator deep-copies queue contents.
     */
    Queue &operator=(const Queue &other)
    {
        if (this == &other)
            return *this;
        clear();
        QNode *cur = other._front;
        while (cur)
        {
            enqueue(cur->data);
            cur = cur->next;
        }
        return *this;
    }
};

#endif // QUEUE_HPP