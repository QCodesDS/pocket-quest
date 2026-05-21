/**
 * @file        BST.hpp
 * @brief       Triển khai lớp Cây tìm kiếm nhị phân (Binary Search Tree - BST) tổng quát theo mô hình OOP.
 *
 * Lớp cấu trúc dữ liệu này đóng gói toàn bộ các thuộc tính quản lý liên kết Node vào vùng
 * bảo mật thuộc tính riêng tư (private), cung cấp giao diện lập trình hướng đối tượng (public)
 * an toàn. Hỗ trợ các tác vụ tra cứu, thêm, xóa phần tử với độ phức tạp thời gian trung bình
 * đạt mức logarit O(log n), tích hợp các bộ duyệt cây qua Callback Lambda tối ưu.
 */

#ifndef BST_HPP
#define BST_HPP

/**
 * @class  BST
 * @brief  Lớp cấu trúc dữ liệu Cây tìm kiếm nhị phân (Binary Search Tree).
 * @tparam T Kiểu dữ liệu của các phần tử được lưu trữ trong cây.
 */
template <typename T>
class BST
{
private:
    /**
     * @struct BSTNode
     * @brief  Cấu trúc một phần tử Node nội bộ (Nested Struct) phục vụ việc liên kết dữ liệu cây.
     */
    struct BSTNode
    {
        T data;         ///< Dữ liệu của phần tử
        BSTNode *left;  ///< Con trỏ quản lý nhánh cây con bên trái (Left child)
        BSTNode *right; ///< Con trỏ quản lý nhánh cây con bên phải (Right child)

        /**
         * @brief Khởi tạo một Node cây nhị phân mới với dữ liệu cho trước.
         * @param val Giá trị dữ liệu cần lưu trữ
         */
        BSTNode(const T &val) : data(val), left(nullptr), right(nullptr) {}
    };

    BSTNode *_root; ///< Con trỏ gốc quản lý toàn bộ cấu trúc cây (Root node)
    int _size;      ///< Số lượng phần tử hiện có trong cây

    // ================================================================================
    //  Private Internal Utilities (Các hàm đệ quy hỗ trợ kỹ thuật nội bộ)
    // ================================================================================

    /**
     * @brief  Hàm đệ quy hỗ trợ chèn một giá trị mới vào cây.
     * @param  node     Con trỏ quản lý Node hiện tại đang xét duyệt trong cây
     * @param  val      Giá trị dữ liệu cần chèn vào cây
     * @param  inserted Biến cờ đánh dấu trạng thái chèn thành công (true nếu chèn mới)
     * @return Con trỏ cập nhật lại liên kết cấu trúc cây sau khi xử lý chèn
     */
    BSTNode *_insert(BSTNode *node, const T &val, bool &inserted)
    {
        if (!node)
        {
            inserted = true;
            return new BSTNode(val);
        }
        if (val < node->data)
            node->left = _insert(node->left, val, inserted);
        else if (node->data < val)
            node->right = _insert(node->right, val, inserted);
        // val == node->data -> Quy ước không chèn các phần tử trùng lặp
        return node;
    }

    /**
     * @brief  Tìm kiếm Node chứa giá trị nhỏ nhất thuộc nhánh cây chỉ định.
     * @param  node Con trỏ gốc của nhánh cây con đang xét
     * @return Con trỏ trỏ tới Node có giá trị nhỏ nhất (Node tận cùng bên trái)
     */
    BSTNode *_minNode(BSTNode *node) const
    {
        while (node->left)
            node = node->left;
        return node;
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ loại bỏ một giá trị ra khỏi cấu trúc cây.
     * @param  node  Con trỏ quản lý Node hiện tại đang xét duyệt
     * @param  val   Giá trị dữ liệu cần tìm và xóa khỏi cây
     * @param  found Biến cờ đánh dấu trạng thái tìm thấy phần tử để xóa
     * @return Con trỏ cập nhật lại liên kết cấu trúc cây sau khi giải phóng bộ nhớ
     */
    BSTNode *_remove(BSTNode *node, const T &val, bool &found)
    {
        if (!node)
            return nullptr;
        if (val < node->data)
            node->left = _remove(node->left, val, found);
        else if (node->data < val)
            node->right = _remove(node->right, val, found);
        else
        {
            found = true;
            if (!node->left)
            {
                BSTNode *r = node->right;
                delete node;
                return r;
            }
            if (!node->right)
            {
                BSTNode *l = node->left;
                delete node;
                return l;
            }
            // Trường hợp Node cần xóa có đầy đủ 2 con: Thay thế bằng Inorder Successor
            BSTNode *succ = _minNode(node->right);
            node->data = succ->data;
            bool dummy = false;
            node->right = _remove(node->right, succ->data, dummy);
        }
        return node;
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ tìm kiếm Node lưu trữ giá trị chỉ định trên cây.
     * @param  node Con trỏ quản lý Node hiện tại đang xét duyệt
     * @param  val  Giá trị dữ liệu mục tiêu cần tra cứu
     * @return Con trỏ trỏ tới BSTNode nếu tìm thấy, ngược lại trả về nullptr
     */
    BSTNode *_search(BSTNode *node, const T &val) const
    {
        if (!node)
            return nullptr;
        if (val == node->data)
            return node;
        if (val < node->data)
            return _search(node->left, val);
        return _search(node->right, val);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Giữa (Inorder Traversal: Left -> Root -> Right).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  node Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn   Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _inorder(BSTNode *node, Fn fn) const
    {
        if (!node)
            return;
        _inorder(node->left, fn);
        fn(node->data);
        _inorder(node->right, fn);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Trước (Preorder Traversal: Root -> Left -> Right).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  node Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn   Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _preorder(BSTNode *node, Fn fn) const
    {
        if (!node)
            return;
        fn(node->data);
        _preorder(node->left, fn);
        _preorder(node->right, fn);
    }

    /**
     * @brief  Hàm đệ quy hỗ trợ duyệt cây theo thứ tự Sau (Postorder Traversal: Left -> Right -> Root).
     * @tparam Fn Kiểu của đối tượng hàm xử lý tác vụ duyệt
     * @param  node Con trỏ gốc của nhánh cây con hiện tại xét duyệt
     * @param  fn   Hàm chức năng callback thực thi trên từng dữ liệu phần tử
     */
    template <typename Fn>
    void _postorder(BSTNode *node, Fn fn) const
    {
        if (!node)
            return;
        _postorder(node->left, fn);
        _postorder(node->right, fn);
        fn(node->data);
    }

    /**
     * @brief Hàm đệ quy hỗ trợ giải phóng toàn bộ các Node bộ nhớ động trong nhánh cây.
     * @param node Con trỏ quản lý Node gốc của nhánh cây cần xóa bỏ
     */
    void _clear(BSTNode *node)
    {
        if (!node)
            return;
        _clear(node->left);
        _clear(node->right);
        delete node;
    }

public:
    // ================================================================================
    //  Lifecycle Management (Khởi tạo / Hủy phát triển)
    // ================================================================================

    /**
     * @brief Khởi tạo một đối tượng cây tìm kiếm nhị phân rỗng.
     */
    BST() : _root(nullptr), _size(0) {}

    /**
     * @brief Hủy đối tượng cây, tự động thu hồi toàn bộ vùng nhớ động của các Node trên cây.
     */
    ~BST() { _clear(_root); }

    // ================================================================================
    //  Core Tree Operations (Các thao tác cốt lõi trên Cây)
    // ================================================================================

    /**
     * @brief  Chèn thêm một phần tử giá trị mới vào cấu trúc cây tìm kiếm nhị phân.
     * @note   Độ phức tạp thời gian thuật toán: Trung bình O(log n), Xấu nhất O(n) [Cây bị suy biến].
     *         Nếu giá trị `val` đã tồn tại sẵn trong hệ thống, hàm sẽ bỏ qua và không tăng kích thước.
     * @param  val Giá trị phần tử cần chèn vào cây
     */
    void insert(const T &val)
    {
        bool inserted = false;
        _root = _insert(_root, val, inserted);
        if (inserted)
            _size++;
    }

    /**
     * @brief  Tìm kiếm và loại bỏ phần tử có giá trị tương ứng ra khỏi cây dữ liệu.
     * @note   Độ phức tạp thời gian thuật toán: Trung bình O(log n), Xấu nhất O(n).
     * @param  val Giá trị dữ liệu của phần tử cần xóa bỏ
     */
    void remove(const T &val)
    {
        bool found = false;
        _root = _remove(_root, val, found);
        if (found)
            _size--;
    }

    /**
     * @brief  Tra cứu thực thể Node lưu trữ giá trị cụ thể trong cây.
     * @note   Độ phức tạp thời gian thuật toán: Trung bình O(log n). Phương thức hằng (const).
     * @param  val Giá trị dữ liệu mục tiêu cần tra cứu vị trí
     * @return Con trỏ tới kiểu dữ liệu T nếu tìm thấy, ngược lại trả về nullptr
     */
    T *search(const T &val) const
    {
        BSTNode *node = _search(_root, val);
        return node ? &node->data : nullptr;
    }

    /**
     * @brief  Kiểm tra xem một giá trị cụ thể có tồn tại trong cấu trúc cây hay không.
     * @param  val Giá trị dữ liệu cần kiểm tra sự hiện diện
     * @return true nếu tìm thấy phần tử trong cây, ngược lại trả về false
     */
    bool contains(const T &val) const { return _search(_root, val) != nullptr; }

    /**
     * @brief  Tìm kiếm phần tử có giá trị nhỏ nhất hiện có trên cây.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu nhỏ nhất trên cây
     */
    const T &findMin() const
    {
        BSTNode *cur = _root;
        while (cur->left)
            cur = cur->left;
        return cur->data;
    }

    /**
     * @brief  Tìm kiếm phần tử có giá trị lớn nhất hiện có trên cây.
     * @warning Cần đảm bảo phương thức `empty()` trả về `false` trước khi gọi hàm này.
     * @return Tham chiếu hằng (Const Reference) tới dữ liệu lớn nhất trên cây
     */
    const T &findMax() const
    {
        BSTNode *cur = _root;
        while (cur->right)
            cur = cur->right;
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
    void inorder(Fn fn) const
    {
        _inorder(_root, fn);
    }

    /**
     * @brief  Duyệt cây theo thứ tự trước (Preorder Traversal) phục vụ sao chép cấu trúc hình thái cây.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` xử lý trên từng phần tử
     */
    template <typename Fn>
    void preorder(Fn fn) const
    {
        _preorder(_root, fn);
    }

    /**
     * @brief  Duyệt cây theo thứ tự sau (Postorder Traversal) phù hợp cho các tác vụ giải phóng, tính toán kích thước.
     * @tparam Fn Kiểu của đối tượng hàm (Function, Lambda Expression, Functor)
     * @param  fn Hàm chức năng có chữ ký dạng `void(const T&)` xử lý trên từng phần tử
     */
    template <typename Fn>
    void postorder(Fn fn) const
    {
        _postorder(_root, fn);
    }

    // ================================================================================
    //  Utility / State Functions (Các hàm tiện ích và trạng thái)
    // ================================================================================

    /**
     * @brief  Lấy tổng số lượng phần tử thực tế hiện đang lưu trữ trong cây dữ liệu.
     * @return Số lượng phần tử (Kiểu số nguyên)
     */
    int size() const { return _size; }

    /**
     * @brief  Kiểm tra xem cấu trúc cây tìm kiếm nhị phân hiện tại có đang rỗng hay không.
     * @return true nếu cây rỗng, ngược lại trả về false
     */
    bool empty() const { return _size == 0; }

    /**
     * @brief Xóa toàn bộ nội dung của cây dữ liệu, giải phóng mọi phân vùng bộ nhớ động đã cấp phát.
     */
    void clear()
    {
        _clear(_root);
        _root = nullptr;
        _size = 0;
    }
};

#endif // BST_HPP