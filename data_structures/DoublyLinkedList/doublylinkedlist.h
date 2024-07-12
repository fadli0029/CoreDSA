#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

template <typename T>
class DoublyLinkedList
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
    DoublyLinkedList(): head(nullptr), tail(nullptr), n_nodes(0) {}

    // Copy constructor, deep copy
    DoublyLinkedList(const DoublyLinkedList& other) {
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
          curr->next->prev = curr;
          curr = curr->next;
          other_curr = other_curr->next;
        }
        this->tail = curr;
        this->n_nodes = other.n_nodes;
      }
    }

    // Move constructor, transfer resource (does not perform deep copy)
    DoublyLinkedList(DoublyLinkedList&& other) noexcept {
      this->head = other.head;
      this->tail = other.tail;
      this->n_nodes = other.n_nodes;
      other.head = nullptr;
      other.tail = nullptr;
      other.n_nodes = 0;
    }

    // Destructor
    ~DoublyLinkedList() {
      this->clear();
    }

    // Assignment operator, deep copy
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
      this->clear();
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
          curr->next->prev = curr;
          curr = curr->next;
          other_curr = other_curr->next;
        }
        this->tail = curr;
        this->n_nodes = other.n_nodes;
      }
      return *this;
    }

    // Assignment operator, transfer resource (does not perform deep copy)
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
      this->clear();
      this->head = other.head;
      this->tail = other.tail;
      this->n_nodes = other.n_nodes;
      other.head = nullptr;
      other.tail = nullptr;
      other.n_nodes = 0;
      return *this;
    }

    /**
     * @brief Insert a new node at the beginning of the list.
     * @param data The data to be stored in the new node.
     * @return The pointer to the new node.
     */
    node_ptr push_front(const T& data) {
      node_ptr new_node = new Node(data, this->head, nullptr);
      if (this->head == nullptr) {
        this->head = new_node;
        this->tail = new_node;
      }
      else {
        this->head->prev = new_node;
        this->head = new_node;
      }
      this->n_nodes++;
      return new_node;
    }

    /**
     * @brief Remove the first node of the list.
     * @return True if the first node is removed successfully, false otherwise.
     */
    bool pop_front() {
      if (this->head == nullptr) {
        return false;
      }

      node_ptr temp = this->head;
      this->head = this->head->next;
      if (this->head != nullptr) {
        this->head->prev = nullptr;
      }
      delete temp;
      this->n_nodes--;

      return true;
    }

    /**
     * @brief Get the pointer to the first node of the list.
     * @return The pointer to the first node of the list.
     */
    node_ptr front() {
      return this->head;
    }

    /**
     * @brief Insert a new node at the end of the list.
     * @param data The data to be stored in the new node.
     * @return The pointer to the new node.
     */
    node_ptr push_back(const T& data) {
      node_ptr new_node = new Node(data, nullptr, this->tail);
      if (this->tail == nullptr) {
        this->head = new_node;
        this->tail = new_node;
      }
      else {
        this->tail->next = new_node;
        this->tail = new_node;
      }
      this->n_nodes++;
      return new_node;
    }

    /**
     * @brief Remove the last node of the list.
     * @return True if the first node is removed successfully, false otherwise.
     */
    bool pop_back() {
      if (this->tail == nullptr) {
        return false;
      }

      node_ptr temp = this->tail;
      this->tail = this->tail->prev;
      if (this->tail != nullptr) {
        this->tail->next = nullptr;
      }
      else {
        this->head = nullptr;
      }
      delete temp;
      this->n_nodes--;

      return true;
    }

    /**
     * @brief Get the pointer to the last node of the list.
     * @return The pointer to the last node of the list.
     */
    node_ptr back() {
      return this->tail;
    }

    /**
     * @brief Get the number of nodes in the list.
     * @return The number of nodes in the list.
     */
    int size() {
      return this->n_nodes;
    }

    /**
     * @brief Check if the list is empty.
     * @return True if the list is empty, false otherwise.
     */
    bool empty() {
      return this->n_nodes == 0;
    }

    /**
      * @brief Insert a new node before the given node (pivot).
      * @param pivot The node before which the new node is inserted.
      * @param data The data to be stored in the new node.
      * @return The pointer to the new node.
      */
    node_ptr insert(node_ptr pivot, const T& data) {
      if (pivot == nullptr) {
        return push_front(data);
      }

      node_ptr new_node = new Node(data, pivot, pivot->prev);
      if (pivot->prev != nullptr) {
        pivot->prev->next = new_node;
      }
      pivot->prev = new_node;
      this->n_nodes++;
      return new_node;
    }

    /**
      * @brief Erase the node at the given node (pivot_start).
      * @param pivot_start The node to be erased.
      * @param pivot_end If provided, erase all nodes after pivot_start (including pivot_start)
                         until the node before pivot_end.
      * @return The pointer to the node after the erased node.
      */
    node_ptr erase(node_ptr pivot_start, node_ptr pivot_end=nullptr) {
      if (pivot_start == nullptr) {
        return nullptr;
      }

      // Delete the node at pivot_start.
      if (pivot_end == nullptr) {
        if (pivot_start->prev != nullptr) {
          pivot_start->prev->next = pivot_start->next;
        }
        else {
          this->head = pivot_start->next;
        }
        if (pivot_start->next != nullptr) {
          pivot_start->next->prev = pivot_start->prev;
        }
        else {
          this->tail = pivot_start->prev;
        }
        node_ptr temp = pivot_start->next; // so we can return node after erased node
        delete pivot_start;
        this->n_nodes--;

        return temp;
      }

      // Delete all nodes at pivot_start until the node before pivot_end.
      else {
        node_ptr temp = pivot_start;
        while (temp != pivot_end) {
          node_ptr next_node = temp->next;
          if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
          }
          else {
            this->head = temp->next;
          }
          if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
          }
          else {
            this->tail = temp->prev;
          }
          delete temp;
          this->n_nodes--;
          temp = next_node;
        }
        return temp;
      }
    }

    /**
     * @brief Remove all nodes from the list.
     */
    void clear() {
      node_ptr curr = this->head;
      while (curr != nullptr) {
        node_ptr temp = curr;
        curr = curr->next;
        delete temp;
      }
      this->head = nullptr;
      this->tail = nullptr;
      this->n_nodes = 0;
    }

    /**
     * @brief Print the list.
     */
    void print_list() const {
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

  private:
    node_ptr head;
    node_ptr tail;
    int n_nodes;
};

#endif // end doublylinkedlist.h definition
