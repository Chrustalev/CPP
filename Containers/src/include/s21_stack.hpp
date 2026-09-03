#pragma once

#include <cstddef>           // for size_t
#include <initializer_list>  // for initializer_list
#include <stdexcept>         // for out_of_range
#include <utility>           // for swap

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/stack.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  //-- member functions --//
  stack() : top_(nullptr), size_(0) {}

  stack(std::initializer_list<value_type> const &items)
      : top_(nullptr), size_(0) {
    for (auto item : items) {
      push(item);
    }
  }

  stack(const stack &s) : top_(nullptr), size_(0) { reverseCopy(s); };

  stack(stack &&s) {
    if (&s == this) return;
    top_ = s.top_;
    size_ = s.size_;
    s.top_ = nullptr;
    s.size_ = 0;
  };

  ~stack() {
    while (!empty()) pop();
  }

  stack &operator=(stack &&s) {
    if (&s == this) return *this;
    while (!empty()) pop();
    top_ = s.top_;
    size_ = s.size_;
    s.top_ = nullptr;
    s.size_ = 0;
    return *this;
  }

  stack &operator=(const stack &other) {
    if (&other == this) return *this;
    while (!empty()) pop();
    reverseCopy(other);
    return *this;
  }

  //-- element access --//
  const_reference top() {
    if (empty()) throw std::out_of_range("Stack is empty");
    return top_->data;
  }

  //-- capacity --//
  bool empty() const { return (size_ == 0); }
  size_type size() const { return size_; };

  //-- modifiers --//
  void push(const_reference value) {
    Node *newNode = new Node(value);
    newNode->prev = top_;
    top_ = newNode;
    ++size_;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto arg : {args...}) {
      push(arg);
    };
  }

  void pop() {
    if (empty()) throw std::out_of_range("Stack is empty");
    Node *temp = top_;
    top_ = top_->prev;
    delete temp;
    --size_;
  }

  void swap(stack &other) {
    if (&other == this) return;
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
  }

 private:
  // some private methods
  void reverseCopy(const stack &other) {
    stack tempStack{};
    Node *curNode = other.top_;
    while (curNode != nullptr) {
      tempStack.push(curNode->data);
      curNode = curNode->prev;
    }

    curNode = tempStack.top_;
    while (curNode != nullptr) {
      this->push(curNode->data);
      curNode = curNode->prev;
    }
  }

  // some private fields
  struct Node {
    value_type data;
    Node *prev;
    Node(const_reference value) : data(value), prev(nullptr) {}
  };

  Node *top_;
  size_type size_;
};
}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)