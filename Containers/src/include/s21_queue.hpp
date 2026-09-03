#pragma once

#include <cstddef>           // for size_t
#include <initializer_list>  // for initializer_list
#include <stdexcept>         // for out_of_range
#include <utility>           // for swap

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/queue.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {

template <typename T>
class queue {
 public:
  //-- member type --//
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  //-- member functions --//
  queue() : head_(nullptr), tail_(nullptr), size_(0) {}

  queue(std::initializer_list<value_type> const &items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (auto item : items) {
      push(item);
    }
  }

  queue(const queue &q) : head_(nullptr), tail_(nullptr), size_(0) {
    Node *temp = q.head_;
    while (temp != nullptr) {
      push(temp->data);
      temp = temp->next;
    }
  }

  queue(queue &&q) {
    if (&q == this) return;
    head_ = q.head_;
    tail_ = q.tail_;
    size_ = q.size_;
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;
  }

  ~queue() {
    while (!empty()) pop();
  }

  queue &operator=(queue &&q) {
    if (&q == this) return *this;

    while (!empty()) pop();

    head_ = q.head_;
    tail_ = q.tail_;
    size_ = q.size_;

    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;

    return *this;
  }

  queue &operator=(const queue &other) {
    if (&other == this) return *this;
    while (!empty()) pop();

    Node *temp = other.head_;
    while (temp != nullptr) {
      push(temp->data);
      temp = temp->next;
    }

    return *this;
  }

  //-- element access --//
  const_reference front() {
    if (empty()) throw std::out_of_range("Queue is empty");
    return head_->data;
  }

  const_reference back() {
    if (empty()) throw std::out_of_range("Queue is empty");
    return tail_->data;
  }

  //-- capacity --//
  bool empty() const { return (size_ == 0); }
  size_type size() const { return size_; };

  //-- modifiers --//
  void push(const_reference value) {
    Node *newNode = new Node(value);
    if (empty()) {
      head_ = newNode;
    } else {
      tail_->next = newNode;
    }
    tail_ = newNode;
    ++size_;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto arg : {args...}) {
      push(arg);
    };
  }

  void pop() {
    if (empty()) throw std::out_of_range("Queue is empty");
    Node *temp = head_;
    head_ = head_->next;
    delete temp;
    --size_;
    if (head_ == nullptr) {
      tail_ = nullptr;
      size_ = 0;
    }
  }

  void swap(queue &other) {
    if (&other == this) return;
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

 private:
  // some private fields
  struct Node {
    value_type data;
    Node *next;
    Node(const_reference value) : data(value), next(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  size_type size_;
};

}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)