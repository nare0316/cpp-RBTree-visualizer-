enum class Color {RED, BLACK};

template <typename T>
struct  Node{
   T val;
   Color color;
   Node *left;
   Node *right;
   Node *parent;
  
  
   Node(T val = T(), Color color = Color::RED, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr) :
        val(val), color(color), left(left), right(right), parent(parent) {}
};

template <typename T>
class RBTree {
    private:
        Node<T> *NIL;;
        Node<T> *root;
    public:
        RBTree()  {
            NIL = new Node<T>();
            NIL->color = Color::BLACK;
            NIL->left = NIL;
            NIL->right = NIL;
            NIL->parent = NIL;

            root = NIL;
        }
        RBTree(const RBTree&) = delete;
        RBTree& operator=(const RBTree&) = delete;
        
        void insert(const T& value);
        void remove(const T& value);
        bool contains(const T& value) const;
        Node<T>* search(const T& value) const;
        void inorder() const;
        void preorder() const;
        void postorder() const;
        Node<T>* getRoot() const;
        Node<T>* getNIL() const;
        Node<T>* getMin(Node<T> *node) const;
        Node<T>* getMax(Node<T> *node) const;
        ~RBTree();
    private:
        void rotateLeft(Node<T> *x);
        void rotateRight(Node<T> *x);
        void fixInsert(Node<T> *node);
        void transplant(Node<T> *u, Node<T> *v);
        void deleteFixup(Node<T> *x);
        void inorder_helper(Node<T> *root) const;
        void preorder_helper(Node<T> *root) const;
        void postorder_helper(Node<T> *root) const;
        void destroy(Node<T> *root);

};






