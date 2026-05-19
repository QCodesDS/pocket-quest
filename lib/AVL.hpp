/**
 * @file        AVL.hpp
 * @brief       Triển khai lớp Cây tìm kiếm nhị phân tự cân bằng (AVL Tree) tổng quát theo mô hình OOP.
 *
 * Lớp cấu trúc dữ liệu này đóng gói toàn bộ các thuộc tính quản lý liên kết Node và thông tin
 * chiều cao (Height) vào vùng bảo mật riêng tư (private). Lớp cung cấp giao diện lập trình công khai
 * an toàn, tự động thực hiện các phép quay cây (Rotations) để duy trì hệ số cân bằng lý tưởng.
 * Đảm bảo thời gian thực thi các tác vụ thêm, xóa, tìm kiếm luôn ổn định ở mức logarit O(log n).
 */

#ifndef AVL_HPP
#define AVL_HPP

/**
 * @class  AVL
 * @brief  Lớp cấu trúc dữ liệu Cây tự cân bằng AVL (Adelson-Velsky and Landis).
 * @tparam T Kiểu dữ liệu của các phần tử được lưu trữ trong cây.
 */
template <typename T>
class AVL {
private:
    /**
     * @struct AVLNode
     * @brief  Cấu trúc một phần tử Node nội bộ (Nested Struct) chứa dữ liệu và chiều cao của nút cây.
     */
    struct AVLNode {
        T data;          ///< Dữ liệu của phần tử
        AVLNode* left;   ///< Con trỏ quản lý nhánh cây con bên trái (Left child)
        AVLNode* right;  ///< Con trỏ quản lý nhánh cây con bên phải (Right child)
        int height;      ///< Chiều cao của Node tính từ đáy phục vụ việc tính toán độ cân bằng

        /**
         * @brief Khởi tạo một Node AVL mới với dữ liệu cho trước.
         * @param val Giá trị dữ liệu cần lưu trữ
         */
        AVLNode(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* _root;  ///< Con trỏ gốc quản lý toàn bộ cấu trúc cây (Root node)
    int _size;       ///< Số lượng phần tử hiện có trong cây

    // ================================================================================
    //  Private Internal Utilities (Các hàm hỗ trợ kỹ thuật và quay cây nội bộ)
    // ================================================================================

    /**
     * @brief  Hàm tiện ích tìm giá trị lớn hơn giữa hai số nguyên.
     * @param  a Số nguyên thứ nhất
     * @param  b Số nguyên thứ hai
     * @return Giá trị lớn nhất trong hai số
     */
    int _max(int a, int b) const { return a > b ? a : b; }

    /**
     * @brief  Lấy chiều cao (Height) an toàn của một Node.
     * @param  n Con trỏ quản lý Node cần kiểm tra
     * @return Chiều cao của Node (trả về 0 nếu con trỏ là nullptr)
     */
    int _height(AVLNode* n) const { return n ? n->height : 0; }

    /**
     * @brief  Tính toán hệ số cân bằng (Balance Factor) của một Node.
     * @param  n Con trỏ quản lý Node cần tính toán
     * @return Hiệu số chiều cao giữa cây con trái và cây con phải (Left Height - Right Height)
     */
    int _bf(AVLNode* n) const { return n ? _height(n->left) - _height(n->right) : 0; }

    /**
     * @brief Cập nhật lại chiều cao của Node dựa trên chiều cao tối đa của các Node con trực thuộc.
     * @param n Con trỏ quản lý Node cần cập nhật
     */
    void _updateHeight(AVLNode* n) {
        if (n) n->height = 1 + _max(_height(n->left), _height(n->right));
    }

    /**
     * @brief  Thực hiện kỹ thuật quay đơn sang phải (Right Rotation / LL Case).
     * @param  y Con trỏ quản lý nút mất cân bằng (gốc của cụm xoay)
     * @return Con trỏ quản lý Node gốc mới của nhánh cây sau khi quay
     */
    AVLNode* _rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* B = x->right;
        x->right = y;
        y->left = B;
        _updateHeight(y);
        _updateHeight(x);
        return x;
    }

    /**
     * @brief  Thực hiện kỹ thuật quay đơn sang trái (Left Rotation / RR Case).
     * @param  x Con trỏ quản lý nút mất cân bằng (gốc của cụm xoay)
     * @return Con trỏ quản lý Node gốc mới của nhánh cây sau khi quay
     */
    AVLNode* _rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* B = y->left;
        y->left = x;
        x->right = B;
        _updateHeight(x);
        _updateHeight(y);
        return y;
    }

    /**
     * @brief  Kiểm tra và thực thi các phép quay cân bằng lại nhánh cây nếu có sự sai lệch chiều cao.
     * @param  n Con trỏ quản lý nút gốc của nhánh cây cần kiểm tra cân bằng
     * @return Con trỏ quản lý nút gốc mới của nhánh cây sau khi đã xử lý cân bằng
     */
    AVLNode* _balance(AVLNode* n) {
        _updateHeight(n);
        int bf = _bf(n);

        // Trường hợp mất cân bằng Trái - Trái (Left-Left Case)
        if (bf > 1 && _bf(n->left) >= 0) return _rotateRight(n);

        // Trường hợp mất cân bằng Trái - Phải (Left-Right Case)
        if (bf > 1 && _bf(n->left) < 0) {
            n->left = _rotateLeft(n->left);
            return _rotateRight(n);
        }

        // Trường hợp mất cân bằng Phải - Phải (Right-Right Case)
        if (bf < -1 && _bf(n->right) <= 0) return _rotateLeft(n);

        // Trường hợp mất cân bằng Phải - Trái (Right-Left Case)
        if (bf < -1 && _bf(n->right) > 0) {
            n->right = _rotateRight(n->right);
            return _rotateLeft(n);
        }

        return n;
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ chèn một giá trị mới và tự động cân bằng lại cây từ dưới lên.
     * @param  n        Con trỏ quản lý Node hiện tại đang xét duyệt
     * @param  val      Giá trị dữ liệu cần chèn vào cây
     * @param  inserted Biến cờ đánh dấu trạng thái chèn thành công (true nếu chèn mới)
     * @return Con trỏ cập nhật liên kết cấu trúc nhánh cây sau khi xử lý chèn và cân bằng
     */
    AVLNode* _insert(AVLNode* n, const T& val, bool& inserted) {
        if (!n) {
            inserted = true;
            return new AVLNode(val);
        }
        if (val < n->data)
            n->left = _insert(n->left, val, inserted);
        else if (n->data < val)
            n->right = _insert(n->right, val, inserted);
        return _balance(n);
    }

    /**
     * @brief  Tìm kiếm Node chứa giá trị nhỏ nhất thuộc nhánh cây chỉ định.
     * @param  n Con trỏ gốc của nhánh cây con đang xét
     * @return Con trỏ trỏ tới Node có giá trị nhỏ nhất (Node tận cùng bên trái)
     */
    AVLNode* _minNode(AVLNode* n) const {
        while (n->left) n = n->left;
        return n;
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ xóa một giá trị ra khỏi cây và tự động tái cân bằng hệ thống.
     * @param  n     Con trỏ quản lý Node hiện tại đang xét duyệt
     * @param  val   Giá trị dữ liệu cần tìm và xóa khỏi cây
     * @param  found Biến cờ đánh dấu trạng thái tìm thấy phần tử để xóa
     * @return Con trỏ cập nhật liên kết cấu trúc nhánh cây sau khi xóa và cân bằng
     */
    AVLNode* _remove(AVLNode* n, const T& val, bool& found) {
        if (!n) return nullptr;
        if (val < n->data)
            n->left = _remove(n->left, val, found);
        else if (n->data < val)
            n->right = _remove(n->right, val, found);
        else {
            found = true;
            if (!n->left || !n->right) {
                AVLNode* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            // Trường hợp Node có cả 2 con: Thay bằng Inorder Successor ở nhánh phải
            AVLNode* succ = _minNode(n->right);
            n->data = succ->data;
            bool dummy = false;
            n->right = _remove(n->right, succ->data, dummy);
        }
        return _balance(n);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ tra cứu Node chứa giá trị chỉ định.
     * @param  n   Con trỏ quản lý Node hiện tại đang xét duyệt
     * @param  val Giá trị dữ liệu mục tiêu cần tìm kiếm
     * @return Con trỏ trỏ tới AVLNode nếu tìm thấy, ngược lại trả về nullptr
     */
    AVLNode* _search(AVLNode* n, const T& val) const {
        if (!n) return nullptr;
        if (val == n->data) return n;
        if (val < n->data) return _search(n->left, val);
        return _search(n->right, val);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Giữa (Inorder Traversal: Left -> Root -> Right).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  n  Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _inorder(AVLNode* n, Fn fn) const {
        if (!n) return;
        _inorder(n->left, fn);
        fn(n->data);
        _inorder(n->right, fn);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Trước (Preorder Traversal: Root -> Left -> Right).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  n  Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _preorder(AVLNode* n, Fn fn) const {
        if (!n) return;
        fn(n->data);
        _preorder(n->left, fn);
        _preorder(n->right, fn);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Sau (Postorder Traversal: Left -> Right -> Root).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  n  Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _postorder(AVLNode* n, Fn fn) const {
        if (!n) return;
        _postorder(n->left, fn);
        _postorder(n->right, fn);
        fn(n->data);
    }

    /**
     * @brief Hàm đệ quy hỗ trợ giải phóng toàn bộ các Node bộ nhớ động của cấu trúc cây.
     * @param n Con trỏ quản lý Node gốc của nhánh cây cần xóa bỏ
     */
    void _clear(AVLNode* n) {
        if (!n) return;
        _clear(n->left);
        _clear(n->right);
        delete n;
    }

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một đối tượng cây AVL rỗng.
     */
    AVL() : _root(nullptr), _size(0) {}

    /**
     * @brief Hủy đối tượng cây AVL, tự động thu hồi toàn bộ vùng nhớ động của các nút trên cây.
     */
    ~AVL() { _clear(_root); }

    // ================================================================================
    //  Core AVL Operations (Các thao tác cốt lõi trên Cây AVL)
    // ================================================================================

    /**
     * @brief  Chèn thêm một phần tử mới vào cây AVL và tự động thực hiện cân bằng.
     * @note   Độ phức tạp thời gian thuật toán đảm bảo ổn định ở mức O(log n).
     *         Nếu giá trị `val` đã tồn tại sẵn, hàm sẽ tự động bỏ qua (không chèn trùng lặp).
     * @param  val Giá trị phần tử cần chèn vào cây
     */
    void insert(const T& val) {
        bool inserted = false;
        _root = _insert(_root, val, inserted);
        if (inserted) _size++;
    }

    /**
     * @brief  Tìm kiếm và loại bỏ phần tử ra khỏi cây dữ liệu, đồng thời tái cấu trúc cân bằng.
     * @note   Độ phức tạp thời gian thuật toán đảm bảo ổn định ở mức O(log n).
     * @param  val Giá trị dữ liệu của phần tử cần xóa bỏ
     */
    void remove(const T& val) {
        bool found = false;
        _root = _remove(_root, val, found);
        if (found) _size--;
    }

    /**
     * @brief  Tra cứu thực thể Node chứa giá trị cụ thể trên cây.
     * @note   Độ phức tạp thời gian thuật toán: O(log n). Phương thức hằng (const).
     * @param  val Giá trị dữ liệu mục tiêu cần tra cứu vị trí
     * @return Con trỏ AVLNode chứa dữ liệu nếu tìm thấy, ngược lại trả về nullptr
     */
    AVLNode* search(const T& val) const { return _search(_root, val); }

    /**
     * @brief  Kiểm tra xem một giá trị cụ thể có tồn tại trong cây AVL hay không.
     * @param  val Giá trị dữ liệu cần kiểm tra sự hiện diện
     * @return true nếu tìm thấy phần tử, ngược lại trả về false
     */
    bool contains(const T& val) const { return _search(_root, val) != nullptr; }

    /**
     * @brief  Tìm kiếm phần tử có giá trị nhỏ nhất hiện có trên cây AVL.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu nhỏ nhất trên cây
     */
    const T& findMin() const {
        AVLNode* cur = _root;
        while (cur->left) cur = cur->left;
        return cur->data;
    }

    /**
     * @brief  Tìm kiếm phần tử có giá trị lớn nhất hiện có trên cây AVL.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu lớn nhất trên cây
     */
    const T& findMax() const {
        AVLNode* cur = _root;
        while (cur->right) cur = cur->right;
        return cur->data;
    }

    // ================================================================================
    //  Callback-driven Traversal (Các hàm duyệt cây qua Callback Lambda)
    // ================================================================================

    /**
     * @brief  Duyệt cây theo thứ tự giữa (Inorder Traversal) mang lại danh sách phần tử có thứ tự tăng dần.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` xử lý trên từng phần tử
     */
    template <typename Fn>
    void inorder(Fn fn) const {
        _inorder(_root, fn);
    }

    /**
     * @brief  Duyệt cây theo thứ tự trước (Preorder Traversal) phục vụ cấu trúc hình thái cây.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` xử lý trên từng phần tử
     */
    template <typename Fn>
    void preorder(Fn fn) const {
        _preorder(_root, fn);
    }

    /**
     * @brief  Duyệt cây theo thứ tự sau (Postorder Traversal) phù hợp giải phóng bộ nhớ hoặc tính toán.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` xử lý trên từng phần tử
     */
    template <typename Fn>
    void postorder(Fn fn) const {
        _postorder(_root, fn);
    }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Lấy tổng số lượng phần tử thực tế đang quản lý trong cây AVL.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief  Kiểm tra xem cấu trúc cây AVL hiện tại có đang rỗng hay không.
     * @return true nếu cây rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief Xóa toàn bộ nội dung của cây, giải phóng mọi phân vùng bộ nhớ động đã cấp phát.
     */
    void clear() {
        _clear(_root);
        _root = nullptr;
        _size = 0;
    }
};

#endif  // AVL_HPP