#ifndef BST_H
#define BST_H

template <typename T>
class BST {
  public:
    struct Node
    {
      T data;
      Node* left;
      Node* right;
      Node* parent;

      Node(
        const T& data,
        Node* left = nullptr,
        Node* right = nullptr,
        Node* parent = nullptr
      ) : data(data), left(left), right(right), parent(parent) {}

      /**
       * @brief Find the successor of this Node
       * @return Node* Pointer to the successor of this Node, or nullptr if none exists
       */
      Node* successor();
    };

    // Constructor
    BST();

    // Copy constructor, deep copy
    BST(const BST& other);

    // Move constructor, transfer resource (does not perform deep copy)
    BST(BST&& other) noexcept;

    // Destructor
    ~BST();

    // Assignment operator, deep copy
    BST& operator=(const BST& other);

    // Move assignment operator, transfer resource (does not perform deep copy)
    BST& operator=(BST&& other) noexcept;

    /**
     * @brief Insert a new element to this BST
     * @param element The new element to insert
     * @return true if the insertion was successful, otherwise false (e.g. duplicate)
     */
    bool insert(int element);

    /**
     * @brief Find a query element in this BST
     * @param query The query element to find
     * @return true if query exists in this BST, otherwise false
     */
    bool find(const int & query) const;

    /**
     * @brief Return the left-most node in this BST
     * @return The left-most node in this BST
     */
    Node* get_left_most_node();

    /**
     * @brief Remove all elements from the BST
     */
    void clear();

    /**
     * @brief Return the number of elements in the BST
     * @return The number of elements in the BST
     */
    unsigned int size() const;

  private:
      Node* root;
      unsigned int num_elements;
};
#endif // end of BST_H definition
