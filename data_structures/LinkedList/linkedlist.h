#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class LinkedList
{
  public:
    struct Node
    {
      T data;
      Node* next;

      Node(const T& data, Node* next = nullptr)
          : data(data), next(next) {}
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
      * @brief Delete the node with the given data, if more than
      * one node contains the data, delete the first occurence of it.
      */
    bool pop(const T& data);

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

    void print_list() const;

  private:
    int n_nodes;
    node_ptr head;
    node_ptr tail;
};

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
  if (other.head == nullptr) {
    this->head = nullptr;
    this->tail = nullptr;
    this->n_nodes = 0;
  }
  else {
    this->head = new Node(other.head->data);
    node_ptr curr = this->head;
    node_ptr other_curr = other.head->next;
    while (other_curr != nullptr) {
      curr->next = new Node(other_curr->data);
      curr = curr->next;
      other_curr = other_curr->next;
    }
    this->tail = curr;
    this->n_nodes = other.n_nodes;
  }
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept {
  this->head = other.head;
  this->tail = other.tail;
  this->n_nodes = other.n_nodes;
  other.head = nullptr;
  other.tail = nullptr;
  other.n_nodes = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
  this->clear();
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
  if (this == &other) {
    return *this;
  }
  this->clear();
    std::cout << "ALDKJA" << std::endl;
  if (other.head == nullptr) {
    this->head = nullptr;
    this->tail = nullptr;
    this->n_nodes = 0;
  }
  else {
    this->head = new Node(other.head->data);
    node_ptr curr = this->head;
    node_ptr other_curr = other.head->next;
    while (other_curr != nullptr) {
      curr->next = new Node(other_curr->data);
      curr = curr->next;
      other_curr = other_curr->next;
    }
    this->tail = curr;
    this->n_nodes = other.n_nodes;
  }
  return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
  this->clear();
  this->head = other.head;
  this->tail = other.tail;
  this->n_nodes = other.n_nodes;
  other.head = nullptr;
  other.tail = nullptr;
  other.n_nodes = 0;
  return *this;
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::push_front(const T& data) {
  node_ptr new_node = new Node(data);
  if (this->head == nullptr) {
    // linked list is empty, there's no head or tail.
    this->head = new_node;
    this->tail = new_node;
  }
  else {
    // replace current head with the new one.
    new_node->next = this->head;
    this->head = new_node;
  }
  this->n_nodes++;
  return this->head;
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::push_back(const T& data) {
  node_ptr new_node = new Node(data);
  if (this->is_empty()) {
    // linked list is empty, there's no head or tail.
    this->head = new_node;
    this->tail = new_node;
  }
  else {
    // replace current tail with the new one.
    this->tail->next = new_node;
    this->tail = new_node;
  }
  this->n_nodes++;
  return this->tail;
}

template<typename T>
bool LinkedList<T>::pop_front() {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty, nothing to pop.";
    return false;
  }
  else if (this->n_nodes == 1) {
    node_ptr temp = this->head;
    this->head = nullptr;
    this->tail = nullptr;
    delete temp;
    this->n_nodes--;
    return true;
  }
  else {
    node_ptr temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->n_nodes--;
    return true;
  }
}

template<typename T>
bool LinkedList<T>::pop_back() {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty, nothing to pop.";
    return false;
  }
  else {
    if (this->n_nodes == 1) {
      return pop_front();
    }
    else {
      node_ptr curr = this->head;
      while (curr->next->next != nullptr) {
        curr = curr->next;
      }
      // curr points to the second last node
      node_ptr temp = curr->next;
      this->tail = curr;
      this->tail->next = nullptr;
      delete temp;
      this->n_nodes--;
      return true;
    }
  }
}

template<typename T>
bool LinkedList<T>::pop(const T& data) {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty, nothing to pop.";
    return false;
  }

  else if (this->n_nodes == 1) {
    return pop_front();
  }

  else {
    node_ptr curr = this->head;
    while (curr->next->data != data || curr->next->next != nullptr) {
      curr = curr->next;
    }

    if (curr->next->next == nullptr) {
      if (curr->next->data == data) {
        return pop_back();
      }
      throw "Node with data not found.";
      return false;
    }

    else {
      node_ptr temp = curr->next;
      curr->next = curr->next->next;
      delete temp;
      this->n_nodes--;
      return true;
    }
  }
}

template<typename T>
T& LinkedList<T>::front() {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    // throw an error
    throw "Linked list is empty.";
  }
  else {
    return head->data;
  }
}

template<typename T>
const T& LinkedList<T>::front() const {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty.";
  }
  else {
    return head->data;
  }
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::get_head() const {
  return this->head;
}

template<typename T>
T& LinkedList<T>::back() {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty.";
  }
  else {
    return tail->data;
  }
}

template<typename T>
const T& LinkedList<T>::back() const {
  if (this->is_empty()) {
    // linked list is empty, nothing to pop
    throw "Linked list is empty.";
  }
  else {
    return tail->data;
  }
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::get_tail() const {
  return this->tail;
}

template<typename T>
int LinkedList<T>::get_size() {
  return this->n_nodes;
}

template<typename T>
bool LinkedList<T>::is_empty() {
  return this->n_nodes == 0;
}

template<typename T>
void LinkedList<T>::clear() {
  while (!this->is_empty()) {
    this->pop_front();
  }
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::find(const T& data) {
  node_ptr curr = this->head;
  if (curr->data == data) {
    return curr;
  }

  while (curr->data != data || curr->next != nullptr) {
    curr = curr->next;
  }

  if (curr->next == nullptr) {
    if (curr->data != data) {
      throw "Node with data not found.";
      return nullptr;
    }
    else {
      return curr;
    }
  }

  else {
    return curr;
  }
}

template<typename T>
typename LinkedList<T>::node_ptr LinkedList<T>::insert_after(node_ptr pivot, const T& data) {
  node_ptr new_node = new Node(data, pivot->next);
  pivot->next = new_node;
  return new_node;
}

template<typename T>
void LinkedList<T>::print_list() const {
  node_ptr curr = this->head;
  std::cout << "[";
  while (curr != nullptr) {
    if (curr->next == nullptr) {
      std::cout << curr->data;
    }
    else {
      std::cout << curr->data << ", ";
    }
    curr = curr->next;
  }
  std::cout << "]" << std::endl;
}

#endif // end linkedlist.h definition
