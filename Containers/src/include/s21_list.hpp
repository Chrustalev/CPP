#pragma once

#include <cstddef>
#include <initializer_list>
#include <ostream>

// TODO : метод splice iterator или const_iterator
// TODO : метод insert_many iterator или const_iterator

// вырезка из readme.md
// список необходимо реализовывать через структуру списка, а не через
// массив

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/list.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {
template <typename T>
class list {
  // fwd dec
  class ListIterator;
  class ListConstIterator;

 public:
  //-- member type --//
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  //-- functions --//
  list() : head_{nullptr}, tail_{nullptr}, size_{0} {}

  list(size_type n) : head_{nullptr}, tail_{nullptr}, size_{0} {
    for (size_type i = 0; i < n; ++i) push_back(T{});
  }

  list(std::initializer_list<value_type> const &items)
      : head_{nullptr}, tail_{nullptr}, size_{0} {
    for (auto item : items) {
      push_back(item);
    }
  }

  list(const list &l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(it);
    }
  }

  list(list &&l) {
    if (&l == this) return;
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  ~list() { clear(); }

  list &operator=(list &&l) {
    if (&l == this) return *this;
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  };

  list &operator=(const list &l) {
    if (&l == this) return *this;
    clear();
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(it);
    }
  };

  //-- element access --//
  const_reference front() const { return head_->data; }
  const_reference back() const { return tail_->data; }

  //-- iterators --//
  iterator begin() { return iterator(head_); }
  const_iterator begin() const { return const_iterator(head_); }
  const_iterator cbegin() const noexcept { return const_iterator(head_); }

  iterator end() { return iterator(empty() ? nullptr : tail_->next); }
  const_iterator end() const {
    return const_iterator(empty() ? nullptr : tail_->next);
  }

  const_iterator cend() const noexcept {
    return const_iterator(empty() ? nullptr : tail_->next);
  }

  //-- capacity --//
  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; };
  size_type max_size() const { return std::numeric_limits<value_type>::max(); }

  //-- modifiers --//
  void clear() {
    while (head_ != nullptr) {
      Node *temp = head_;
      head_ = head_->next;
      delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
  }

  /**
   * @brief метод для вставки значения по указанному итератору
   */
  iterator insert(iterator pos, const_reference value) {
    Node *node = new Node(value);

    // если позиция итератора на начало списка
    if (empty()) {
      head_ = node;
      tail_ = node;
    } else if (pos == begin()) {
      node->next = head_;
      head_->prev = node;
      head_ = head_->prev;
    } else if (pos == end()) {
      tail_->next = node;
      node->prev = tail_;
      tail_ = node;
    } else {
      // получаем указатель на текущий узел
      Node *current = pos.getNode();
      // вставляем новый узел до текущего узла
      node->next = current;
      node->prev = current->prev;
      current->prev->next = node;
      current->prev = node;
    }
    ++size_;
    return iterator(node);
  }

  iterator insert(const_iterator pos, const_reference value) {
    Node *node = new Node(value);

    // если позиция итератора на начало списка
    if (empty()) {
      head_ = node;
      tail_ = node;
    } else if (pos == cbegin()) {
      node->next = head_;
      head_->prev = node;
      head_ = head_->prev;
    } else if (pos == cend()) {
      tail_->next = node;
      node->prev = tail_;
      tail_ = node;
    } else {
      // получаем указатель на текущий узел
      Node *current = pos.cgetNode();
      // вставляем новый узел до текущего узла
      node->next = current;
      node->prev = current->prev;
      current->prev->next = node;
      current->prev = node;
    }
    ++size_;
    return iterator(node);
  }

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    for (auto &arg : {args...}) {
      insert(pos, arg);
    }
    return head_;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    insert_many(begin(), args...);
  }

  void erase(iterator pos) {
    Node *node = pos.getNode();
    if (node == nullptr) throw std::string("Iterator is out of range");

    // если указатель узла это первый узел списка
    if (node == head_) {
      // смещаем указатель головы на следующий узел
      head_ = head_->next;
      // если следующий узел существует
      if (head_ != nullptr)
        // то указатель на предыдущий узел равен nullptr
        head_->prev = nullptr;

    }  // иначе, указатель узла на последний узел списка
    else if (node == tail_) {
      // указатель последнего узла равен предпоследнему узлу
      tail_ = tail_->prev;
      if (tail_ != nullptr)
        // указатель на следующий узел равен nullptr
        tail_->next = nullptr;
    }  // иначе, узел в середине списка
    else {
      // связываем указатели предыдущего и последующего узла
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
    // удаляем текущий узел, освобождаем память
    delete node;
    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(tail_); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }

  void swap(list &other) {
    if (&other == this) return;
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(list &other) {
    if (this != &other) {
      auto it = begin();
      auto otherIt = other.begin();

      while (otherIt != other.end()) {
        if (it == end() || *otherIt < *it) {
          insert(it, *otherIt);
          ++otherIt;
        } else {
          ++it;
        }
      }
      other.clear();
    }
  }

  void splice(iterator pos, list &other) {
    if (this != &other) {
      for (auto it : other) {
        insert(pos, it);
      }
      other.clear();
    }
  }

  void reverse() {
    Node *temp = head_;
    while (temp != nullptr) {
      std::swap(temp->next, temp->prev);
      temp = temp->prev;
    }
    std::swap(head_, tail_);
  }

  void unique() {
    if (size_ > 1) {
      Node *cur = head_;
      while (cur->next != nullptr) {
        Node *curNext = cur->next;
        if (cur->data == curNext->data) {
          erase(cur);
        }
        cur = curNext;
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      bool sorted;
      Node *temp;

      do {
        sorted = true;
        temp = head_;
        while (temp->next != nullptr) {
          if (temp->data > temp->next->data) {
            std::swap(temp->data, temp->next->data);
            sorted = false;
          }
          temp = temp->next;
        }
      } while (!sorted);
    }
  }

 private:
  // some private fields
  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    Node(const_reference value) {
      data = value;
      prev = nullptr;
      next = nullptr;
    }
  };

  Node *head_;
  Node *tail_;
  size_type size_;
};

template <typename T>
class list<T>::ListIterator {
 public:
  ListIterator(typename list<T>::Node *node) { node_ = node; }

  // operators
  reference operator*() const { return node_->data; }

  ListIterator &operator++() {
    node_ = node_->next;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const ListIterator &other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListIterator &other) const { return !(*this == other); }

  typename list<T>::Node *getNode() { return node_; }

 private:
  typename list<T>::Node *node_;
};

template <typename T>
class list<T>::ListConstIterator {
 public:
  // constructor
  ListConstIterator(const typename list<T>::Node *node) : node_(node) {}

  // operators
  const_reference operator*() const { return node_->data; }

  ListConstIterator &operator++() {
    node_ = node_->next;
    return *this;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const ListConstIterator &other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListConstIterator &other) const {
    return !(*this == other);
  }

  const typename list<T>::Node *cgetNode() { return node_; }

 private:
  const typename list<T>::Node *node_;
};
}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)