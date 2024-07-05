#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList
{
  public:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& data, Node* next = nullptr, Node* prev = nullptr)
            : data(data), next(next), prev(prev) {}
    };
    using node_ptr = Node*;

    // Constructor
    LinkedList();

    // Copy constructor, deep copy
    LinkedList(const LinkedList& other);

    // Copy constructor, transfer resource (does not perform deep copy)
    LinkedList(LinkedList&& other) noexcept;

    // Destructor
    ~LinkedList();

    // Assignment operator, deep copy
    LinkedList& operator=(const LinkedList& other);

    // Assignment operator, transfer resource (does not perform deep copy)
    LinkedList& operator=(LinkedList&& other) noexcept;

    // Data-structure-specific member functions:

    /**
     * @brief Insert a new node at the beginning of the list.
     * @param data The data to be stored in the new node.
     */
    node_ptr push_front(const T& data);

    /**
     * @brief Insert a new node at the end of the list.
     * @param data The data to be stored in the new node.
     */
    node_ptr push_back(const T& data);

    /**
     * @brief Remove the first node of the list.
     */
    bool pop_front();

    /**
     * @brief Remove the last node of the list.
     */
    bool pop_back();

    /**
     * @brief Get the data stored in the first node of the list. Allow mutable access.
     * @return The data stored in the first node of the list.
     */
    T& front();


    /**
     * @brief Get the data stored in the first node of the list. Allow const access.
     * @return The data stored in the first node of the list.
     */
    const T& front() const;

    /**
     * @brief Get the pointer to the first node of the list. Allow const access.
     * @return The pointer to the first node of the list.
     */
    node_ptr get_head() const;

    /**
     * @brief Get the data stored in the last node of the list. Allow mutable access.
     * @return The data stored in the last node of the list.
     */
    T& back();

    /**
     * @brief Get the data stored in the last node of the list. Allow const access.
     * @return The data stored in the last node of the list.
     */
    const T& back() const;

    /**
     * @brief Get the pointer to the last node of the list. Allow const access.
     * @return The pointer to the last node of the list.
     */
    node_ptr get_tail() const;

    /**
     * @brief Get the number of nodes in the list.
     * @return The number of nodes in the list.
     */
    int get_size();

    /**
     * @brief Check if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool is_empty();

    /**
     * @brief Remove all nodes from the list.
     */
    void clear();

    /**
      * @brief Delete the first node in the list.
      */
    void delete_front();

    /**
      * @brief Delete the last node in the list.
      */
    void delete_back();

    /**
      * @brief Delete the node with the given data, if more than
      * one node contains the data, return false.
      */
    bool remove(const T& data);

    /**
      * @brief Find the node with the given data, return the pointer to the node.
      * @param data The data to be found.
      * @return The index of the node with the given data.
      */
    node_ptr find(const T& data);

    /**
      * @brief Insert a new node after the given node.
      * @param pivot The node after which the new node is inserted.
      * @param data The data to be stored in the new node.
      * @return The pointer to the new node.
      */
    node_ptr insert_after(node_ptr pivot, const T& data);

  private:
    int n_nodes;
    node_ptr head;
    node_ptr tail;
};

#endif // end linkedlist.h definition
