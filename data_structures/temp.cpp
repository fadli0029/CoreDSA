#include "linkedlist.h"

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
    node_ptr curr = this->head;
    while (curr->next->next != nullptr) {
      curr = curr->next;
    }
    // curr points to the second last node
    node_ptr temp = curr->next;
    this->tail = curr;
    delete temp;
    this->n_nodes--;
    return true;
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
    throw "Linked list is empty.";
    return false;
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
    return false;
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
    return false;
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
    return false;
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

  while (curr->data != data || curr->next != nullptr) {
    curr = curr->next;
  }

  if (curr->next == nullptr) {
    throw "Node with data not found.";
    return nullptr;
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
