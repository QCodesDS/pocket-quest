/**
 * @file        Algorithms.hpp
 * @brief       Thư viện tổng hợp các thuật toán Sắp xếp (Sorting) và Tìm kiếm (Searching) tổng quát.
 *
 * Tệp mã nguồn cung cấp các giải thuật kinh điển được thiết kế dưới dạng hàm mẫu (Template Functions),
 * cho phép cấu hình linh hoạt tiêu chí so sánh dữ liệu thông qua tham số loại Comparator Functor,
 * độc lập hoàn toàn và không phụ thuộc vào các thư viện chuẩn bên ngoài.
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

// ================================================================================
//  Default Comparator (Cấu trúc so sánh mặc định)
// ================================================================================

/**
 * @struct AscComp
 * @brief  Cấu trúc so sánh mặc định tạo điều kiện sắp xếp dữ liệu theo thứ tự tăng dần.
 * @tparam T Kiểu dữ liệu của các phần tử cần thực hiện so sánh.
 */
template <typename T>
struct AscComp {
    /**
     * @brief Toán tử so sánh nhỏ hơn.
     * @return true nếu a nhỏ hơn b, ngược lại trả về false
     */
    bool operator()(const T& a, const T& b) const { return a < b; }
};

// ================================================================================
//  SORTING ALGORITHMS (Các thuật toán sắp xếp dữ liệu)
// ================================================================================

/**
 * @brief  Sắp xếp nổi bọt (Bubble Sort) - Hoán vị liên tiếp các phần tử liền kề sai thứ tự.
 * @note   Độ phức tạp thời gian: Tốt nhất O(n) [đã sắp xếp], Trung bình/Xấu nhất O(n^2).
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  n   Số lượng phần tử của mảng
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void bubbleSort(T* arr, int n, Comp cmp = Comp()) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (cmp(arr[j + 1], arr[j])) {
                T tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

/**
 * @brief  Sắp xếp chọn (Selection Sort) - Tìm phần tử tối ưu trên từng chặng để đưa về vị trí đúng.
 * @note   Độ phức tạp thời gian: O(n^2) cho mọi trường hợp. Thuật toán tối ưu số lần hoán vị (Swap).
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  n   Số lượng phần tử của mảng
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void selectionSort(T* arr, int n, Comp cmp = Comp()) {
    for (int i = 0; i < n - 1; i++) {
        int best = i;
        for (int j = i + 1; j < n; j++)
            if (cmp(arr[j], arr[best])) best = j;
        if (best != i) {
            T tmp = arr[i];
            arr[i] = arr[best];
            arr[best] = tmp;
        }
    }
}

/**
 * @brief  Sắp xếp chèn (Insertion Sort) - Xây dựng mảng đã sắp xếp dần dần bằng cách chèn phần tử vào vị trí thích hợp.
 * @note   Độ phức tạp thời gian: Tốt nhất O(n) [đã sắp xếp], Trung bình/Xấu nhất O(n^2). Hiệu quả với mảng kích thước
 * nhỏ.
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  n   Số lượng phần tử của mảng
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void insertionSort(T* arr, int n, Comp cmp = Comp()) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ── Merge Sort Helpers (Các hàm bổ trợ cho thuật toán Sắp xếp trộn) ─────────────────

/**
 * @brief  Trộn hai mảng con đã được sắp xếp thành một mảng con thống nhất duy nhất.
 * @note   Cấp phát mảng phụ tạm thời trên bộ nhớ Heap nội bộ, giải phóng ngay sau khi hoàn thành.
 * @param  arr Con trỏ trỏ tới mảng dữ liệu gốc
 * @param  lo  Vị trí biên trái của phân đoạn
 * @param  mid Vị trí ranh giới phân chia ở giữa
 * @param  hi  Vị trí biên phải của phân đoạn
 * @param  cmp Thực thể cấu trúc so sánh độ ưu tiên
 */
template <typename T, typename Comp>
void _merge(T* arr, int lo, int mid, int hi, Comp cmp) {
    int n1 = mid - lo + 1, n2 = hi - mid;
    T* L = new T[n1];
    T* R = new T[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[lo + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) arr[k++] = cmp(L[i], R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

/**
 * @brief  Hàm đệ quy bổ trợ phân chia đoạn mảng dữ liệu để xử lý trộn (Merge Sort).
 * @param  arr Con trỏ trỏ tới mảng dữ liệu
 * @param  lo  Vị trí biên trái hiện tại cần xử lý
 * @param  hi  Vị trí biên phải hiện tại cần xử lý
 * @param  cmp Thực thể cấu trúc so sánh độ ưu tiên
 */
template <typename T, typename Comp>
void _mergeSortHelper(T* arr, int lo, int hi, Comp cmp) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    _mergeSortHelper(arr, lo, mid, cmp);
    _mergeSortHelper(arr, mid + 1, hi, cmp);
    _merge(arr, lo, mid, hi, cmp);
}

/**
 * @brief  Sắp xếp trộn (Merge Sort) - Giải thuật chia để trị ổn định (Stable Sort).
 * @note   Độ phức tạp thời gian: O(n log n) cho mọi trường hợp. Tiêu tốn thêm không gian bộ nhớ phụ O(n).
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  n   Số lượng phần tử của mảng
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void mergeSort(T* arr, int n, Comp cmp = Comp()) {
    if (n > 1) _mergeSortHelper(arr, 0, n - 1, cmp);
}

// ── Heap Sort Helpers (Các hàm bổ trợ cho thuật toán Sắp xếp vun đống) ───────────────

/**
 * @brief  Tái cấu trúc lại một cây con có gốc tại chỉ số i để thỏa mãn tính chất Heap.
 * @note   Sử dụng giải thuật đệ quy đuôi để đẩy các phần tử sai vị trí xuống dưới đáy.
 * @param  arr Con trỏ trỏ tới mảng dữ liệu mô hình hóa Heap
 * @param  n   Kích thước vùng dữ liệu Heap hiện tại cần xét
 * @param  i   Chỉ số nút gốc của cây con cần vun đống
 * @param  cmp Thực thể cấu trúc so sánh độ ưu tiên
 */
template <typename T, typename Comp>
void _heapify(T* arr, int n, int i, Comp cmp) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && cmp(arr[largest], arr[l])) largest = l;
    if (r < n && cmp(arr[largest], arr[r])) largest = r;
    if (largest != i) {
        T tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        _heapify(arr, n, largest, cmp);
    }
}

/**
 * @brief  Sắp xếp vun đống (Heap Sort) - Xây dựng cấu trúc cây nhị phân hoàn chỉnh để trích xuất phần tử.
 * @note   Độ phức tạp thời gian: O(n log n) cho mọi trường hợp. Thuật toán sắp xếp tại chỗ (In-place) không tốn bộ nhớ
 * phụ.
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  n   Số lượng phần tử của mảng
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void heapSort(T* arr, int n, Comp cmp = Comp()) {
    for (int i = n / 2 - 1; i >= 0; i--) _heapify(arr, n, i, cmp);
    for (int i = n - 1; i > 0; i--) {
        T tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        _heapify(arr, i, 0, cmp);
    }
}

// ── Quick Sort Helpers (Các hàm bổ trợ cho thuật toán Sắp xếp nhanh) ────────────────

/**
 * @brief  Phân đoạn mảng dựa trên phần tử chốt (Pivot) được chọn ở cuối phân vùng (Lomuto Partition).
 * @note   Đưa toàn bộ phần tử ưu tiên hơn chốt về bên trái, phần tử kém ưu tiên hơn về bên phải.
 * @param  arr Con trỏ trỏ tới mảng dữ liệu
 * @param  lo  Vị trí biên trái của phân vùng dữ liệu xét
 * @param  hi  Vị trí biên phải của phân vùng dữ liệu xét (Vị trí lấy chốt)
 * @param  cmp Thực thể cấu trúc so sánh độ ưu tiên
 * @return Chỉ số vị trí chính xác của phần tử chốt sau khi phân vùng hoàn tất
 */
template <typename T, typename Comp>
int _partition(T* arr, int lo, int hi, Comp cmp) {
    T pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (cmp(arr[j], pivot)) {
            i++;
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    T tmp = arr[i + 1];
    arr[i + 1] = arr[hi];
    arr[hi] = tmp;
    return i + 1;
}

/**
 * @brief  Sắp xếp nhanh (Quick Sort) - Phân vùng chia để trị ngẫu nhiên hiệu năng cực cao.
 * @note   Độ phức tạp thời gian: Trung bình O(n log n), Xấu nhất O(n^2) [khi mảng bị suy biến].
 * @tparam T   Kiểu dữ liệu của các phần tử trong mảng
 * @tparam Comp Kiểu cấu trúc hàm so sánh quyết định thứ tự sắp xếp
 * @param  arr Con trỏ trỏ tới mảng dữ liệu cần sắp xếp
 * @param  lo  Vị trí bắt đầu phân đoạn cần sắp xếp (Thường khởi tạo bằng 0)
 * @param  hi  Vị trí kết thúc phân đoạn cần sắp xếp (Thường khởi tạo bằng n-1)
 * @param  cmp Thực thể cấu trúc so sánh (Mặc định: AscComp<T>)
 */
template <typename T, typename Comp = AscComp<T>>
void quickSort(T* arr, int lo, int hi, Comp cmp = Comp()) {
    if (lo >= hi) return;
    int p = _partition(arr, lo, hi, cmp);
    quickSort(arr, lo, p - 1, cmp);
    quickSort(arr, p + 1, hi, cmp);
}

// ================================================================================
//  SEARCH ALGORITHMS (Các thuật toán tìm kiếm dữ liệu)
// ================================================================================

/**
 * @brief  Tìm kiếm tuyến tính (Linear Search) - Quét duyệt tuần tự mảng thô từ đầu tới cuối.
 * @note   Độ phức tạp thời gian: O(n). Phù hợp với mảng chưa được sắp xếp hoặc kích thước nhỏ.
 * @tparam T   Kiểu dữ liệu của các phần tử cần duyệt
 * @param  arr Con trỏ trỏ tới mảng hằng dữ liệu đầu vào
 * @param  n   Số lượng phần tử có trong mảng
 * @param  key Giá trị mục tiêu cần tìm kiếm vị trí
 * @return Chỉ số index của phần tử nếu tìm thấy, ngược lại trả về -1
 */
template <typename T>
int linearSearch(const T* arr, int n, const T& key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key) return i;
    return -1;
}

/**
 * @brief  Tìm kiếm nhị phân (Binary Search) - Thu hẹp phạm vi dựa trên việc chia đôi khoảng giá trị xét.
 * @warning Mảng đầu vào BẮT BUỘC phải được sắp xếp theo thứ tự tăng dần trước khi thực hiện tìm kiếm.
 * @note   Độ phức tạp thời gian: O(log n) cực nhanh cho cơ sở dữ liệu lớn.
 * @tparam T   Kiểu dữ liệu của các phần tử cần duyệt
 * @param  arr Con trỏ trỏ tới mảng hằng dữ liệu đã được sắp xếp
 * @param  n   Số lượng phần tử có trong mảng
 * @param  key Giá trị mục tiêu cần tìm kiếm vị trí
 * @return Chỉ số index của phần tử nếu tìm thấy, ngược lại trả về -1
 */
template <typename T>
int binarySearch(const T* arr, int n, const T& key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

#endif  // ALGRITHMS_HPP