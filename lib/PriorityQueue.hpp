/**
 * @file        PriorityQueue.hpp
 * @brief       Triển khai lớp Hàng đợi ưu tiên (Priority Queue) tổng quát bằng Binary Heap theo mô hình OOP.
 *
 * Cấu trúc dữ liệu đóng gói một mảng động tự điều chỉnh kích thước (Dynamic Array)
 * để biểu diễn cây nhị phân hoàn chỉnh. Cho phép tùy biến tiêu chí ưu tiên thông qua cấu trúc
 * so sánh (Comparator Functor), tối ưu hiệu năng các tác vụ thêm/xóa ở độ phức tạp logarit O(log n).
 */

#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

// ================================================================================
//  Default Comparators (Các cấu trúc so sánh mặc định)
// ================================================================================

/**
 * @struct Less
 * @brief  Cấu trúc so sánh mặc định tạo điều kiện xây dựng Max-Heap.
 * @tparam T Kiểu dữ liệu của các phần tử cần so sánh.
 */
template <typename T>
struct Less {
    /**
     * @brief Toán tử so sánh nhỏ hơn.
     * @return true nếu a nhỏ hơn b, ngược lại trả về false
     */
    bool operator()(const T& a, const T& b) const { return a < b; }
};

/**
 * @struct Greater
 * @brief  Cấu trúc so sánh tạo điều kiện xây dựng Min-Heap.
 * @tparam T Kiểu dữ liệu của các phần tử cần so sánh.
 */
template <typename T>
struct Greater {
    /**
     * @brief Toán tử so sánh lớn hơn.
     * @return true nếu a lớn hơn b, ngược lại trả về false
     */
    bool operator()(const T& a, const T& b) const { return a > b; }
};

// ================================================================================
//  PriorityQueue Class Definition
// ================================================================================

/**
 * @class  PriorityQueue
 * @brief  Lớp cấu trúc dữ liệu Hàng đợi ưu tiên (Priority Queue) dựa trên cấu trúc Heap.
 * @tparam T   Kiểu dữ liệu của các phần tử trong hàng đợi.
 * @tparam Comp Kiểu cấu trúc so sánh quyết định độ ưu tiên (Mặc định là Less<T> tạo Max-Heap).
 */
template <typename T, typename Comp = Less<T>>
class PriorityQueue {
private:
    T* _heap;   ///< Mảng động lưu trữ các phần tử của Heap
    int _size;  ///< Số lượng phần tử hiện tại trong hàng đợi
    int _cap;   ///< Sức chứa tối đa hiện tại của phân vùng bộ nhớ được cấp phát
    Comp _cmp;  ///< Đối tượng hàm so sánh (Functor) để đánh giá độ ưu tiên

    // ================================================================================
    //  Private Internal Utilities (Các hàm hỗ trợ kỹ thuật nội bộ)
    // ================================================================================

    /**
     * @brief  Sàng lọc lên (Sift-Up / Bubble-Up) để tái cấu trúc lại vị trí phần tử từ dưới lên.
     * @note   Độ phức tạp thời gian thuật toán: O(log n).
     * @param  i Chỉ số của phần tử cần sàng lọc
     */
    void _siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (_cmp(_heap[parent], _heap[i])) {
                T tmp = _heap[parent];
                _heap[parent] = _heap[i];
                _heap[i] = tmp;
                i = parent;
            } else {
                break;
            }
        }
    }

    /**
     * @brief  Sàng lọc xuống (Sift-Down / Sink-Down) để tái cấu trúc lại vị trí phần tử từ trên xuống.
     * @note   Độ phức tạp thời gian thuật toán: O(log n).
     * @param  i Chỉ số của phần tử cần sàng lọc
     */
    void _siftDown(int i) {
        while (true) {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;

            if (l < _size && _cmp(_heap[largest], _heap[l])) largest = l;
            if (r < _size && _cmp(_heap[largest], _heap[r])) largest = r;
            if (largest == i) break;

            T tmp = _heap[i];
            _heap[i] = _heap[largest];
            _heap[largest] = tmp;
            i = largest;
        }
    }

    /**
     * @brief Mở rộng gấp đôi sức chứa (Capacity) của mảng động khi hàng đợi ưu tiên bị đầy.
     */
    void _grow() {
        _cap *= 2;
        T* fresh = new T[_cap];
        for (int i = 0; i < _size; i++) fresh[i] = _heap[i];
        delete[] _heap;
        _heap = fresh;
    }

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một hàng đợi ưu tiên mới.
     * @param cap Sức chứa khởi tạo ban đầu của mảng (Mặc định là 64)
     * @param cmp Thực thể cấu trúc so sánh độ ưu tiên (Mặc định tạo instance mới)
     */
    PriorityQueue(int cap = 64, Comp cmp = Comp()) : _heap(new T[cap]), _size(0), _cap(cap), _cmp(cmp) {}

    /**
     * @brief Hủy đối tượng hàng đợi ưu tiên, tự động giải phóng vùng nhớ động của mảng Heap.
     */
    ~PriorityQueue() { delete[] _heap; }

    // ================================================================================
    //  Core Operations (Các thao tác cốt lõi)
    // ================================================================================

    /**
     * @brief  Chèn thêm một phần tử mới vào hàng đợi ưu tiên và tự động sắp xếp lại Heap.
     * @note   Độ phức tạp thời gian thuật toán: O(log n). Tự động kích hoạt `_grow()` nếu đầy.
     * @param  val Giá trị phần tử cần chèn
     */
    void insert(const T& val) {
        if (_size == _cap) _grow();
        _heap[_size++] = val;
        _siftUp(_size - 1);
    }

    /**
     * @brief  Trích xuất và loại bỏ phần tử có độ ưu tiên cao nhất nằm ở gốc Heap (Chỉ số 0).
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @note   Độ phức tạp thời gian thuật toán: O(log n).
     * @return Giá trị của phần tử có độ ưu tiên cao nhất vừa trích xuất
     */
    T extract() {
        T top = _heap[0];
        _heap[0] = _heap[--_size];
        if (_size > 0) _siftDown(0);
        return top;
    }

    /**
     * @brief  Xem phần tử có độ ưu tiên cao nhất ở gốc Heap mà không loại bỏ nó.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @note   Độ phức tạp thời gian thuật toán: O(1).
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu phần tử ưu tiên cao nhất
     */
    const T& peek() const { return _heap[0]; }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Kiểm tra xem hàng đợi ưu tiên hiện tại có đang rỗng hay không.
     * @return true nếu hàng đợi rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief  Lấy số lượng phần tử hiện thực tế có trong hàng đợi ưu tiên.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief Xóa toàn bộ nội dung trong hàng đợi bằng cách đưa số lượng phần tử về 0.
     * @note  Hàm này giữ nguyên dung lượng mảng bộ nhớ đệm `_cap` để tái sử dụng tối ưu.
     */
    void clear() { _size = 0; }
};

#endif  // PRIORITYQUEUE_HPP