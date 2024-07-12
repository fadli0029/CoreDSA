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
    LinkedList(): head(nullptr), n_nodes(0) {}

    // Copy constructor, deep copy
    LinkedList(const LinkedList& other) {
      if (other.head == nullptr) {
        this->head = nullptr;
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
        this->n_nodes = other.n_nodes;
      }
    }

    // Move constructor, transfer resource (does not perform deep copy)
    LinkedList(LinkedList&& other) noexcept {
      this->head = other.head;
      this->n_nodes = other.n_nodes;
      other.head = nullptr;
      other.n_nodes = 0;
    }

    // Destructor
    ~LinkedList() {
      this->clear();
    }

    // Assignment operator, deep copy
    LinkedList& operator=(const LinkedList& other) {
      this->clear();
      if (other.head == nullptr) {
        this->head = nullptr;
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
        this->n_nodes = other.n_nodes;
      }
      return *this;
    }

    // Assignment operator, transfer resource (does not perform deep copy)
    LinkedList& operator=(LinkedList&& other) noexcept {
      this->clear();
      this->head = other.head;
      this->n_nodes = other.n_nodes;
      other.head = nullptr;
      other.n_nodes = 0;
      return *this;
    }

    /**
     * @brief Insert a new node at the beginning of the list.
     * @param data The data to be stored in the new node.
     * @return The pointer to the new node.
     */
    node_ptr push_front(const T& data) {
      node_ptr new_node = new Node(data, this->head);
      if (this->head == nullptr) {
        // linked list is empty.
        this->head = new_node;
      }
      else {
        // replace current head with the new one.
        this->head = new_node;
      }
      this->n_nodes++;
      return this->head;
    }

    /**
     * @brief Remove the first node of the list.
     * @return True if the first node is removed successfully, false otherwise.
     */
    bool pop_front() {
      if (this->head == nullptr) {
        // linked list is empty, nothing to pop
        return false;
      }
      else {
        node_ptr temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->n_nodes--;
        return true;
      }
    }

    /**
     * @brief Get the pointer to the first node of the list.
     * @return The pointer to the first node of the list.
     */
    node_ptr front() {
      return this->head;
    }

    /**
     * @brief Get the number of nodes in the list.
     * @return The number of nodes in the list.
     */
    unsigned int size() {
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
      * @brief Insert a new node after the given node.
      * @param pivot The node after which the new node is inserted.
      * @param data The data to be stored in the new node.
      * @return The pointer to the new node.
      */
    node_ptr insert_after(node_ptr pivot, const T& data) {
      if (pivot == nullptr) {
        return push_front(data);
      }

      node_ptr new_node = new Node(data, pivot->next);
      pivot->next = new_node;
      this->n_nodes++;
      return new_node;
    }

    /**
      * @brief Erase the node after the given node.
      * @param pivot_start The node after which the node is erased.
      * @param pivot_end The node before which the node is erased.
      * @return The pointer to the node after the erased node.
      */
    node_ptr erase_after(node_ptr pivot_start, node_ptr pivot_end=nullptr) {
      if (pivot_start == nullptr) {
        return nullptr;
      }

      if (pivot_end == nullptr) {
        node_ptr temp = pivot_start->next;
        if (temp == nullptr) {
          return nullptr;
        }
        pivot_start->next = temp->next;
        delete temp;
        this->n_nodes--;

        return pivot_start->next;
      }

      else {
        // Delete all nodes after pivot_start until the node before pivot_end.
        node_ptr temp = pivot_start->next;
        while (temp != pivot_end) {
          node_ptr next = temp->next;
          delete temp;
          this->n_nodes--;
          temp = next;
        }
        pivot_start->next = pivot_end;
        return pivot_end;
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
    unsigned int n_nodes;
};

#endif // end of linkedlist.h definition
