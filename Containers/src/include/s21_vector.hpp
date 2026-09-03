#pragma once

#include <algorithm>         // for copy
#include <cstddef>           // for size_t
#include <initializer_list>  // for initializer_list
#include <limits>            // for numeric_limits
#include <stdexcept>         // for out_of_range
#include <utility>           // for swap

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/vector.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = size_t;

  //-- member functions --//
  vector() : size_{0}, capacity_{0}, container_{nullptr} {}

  vector(size_type n) {
    size_type a = n;
    if (n > 0 && a < max_size()) {
      this->size_ = n;
      this->capacity_ = n;
      this->container_ = new value_type[n];
    } else {
      throw std::out_of_range("cannot create s21::vector");
    }
  }

  vector(std::initializer_list<value_type> const &items)
      : size_{items.size()}, capacity_{items.size()} {
    if (this->size_ > 0) {
      this->container_ = new value_type[this->size_];
      std::copy(items.begin(), items.end(), container_);
    } else {
      this->size_ = 0;
      this->capacity_ = 0;
      this->container_ = nullptr;
    }
  }

  vector(const vector &v)
      : size_(v.size_),
        capacity_(v.capacity_),
        container_(new value_type[v.capacity_]) {
    for (size_type i = 0; i < this->size_; i++) {
      this->container_[i] = v.container_[i];
    }
  }

  vector(vector &&v) noexcept
      : size_(v.size_), capacity_(v.capacity_), container_(v.container_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.container_ = nullptr;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] this->container_;
      this->size_ = 0;
      this->capacity_ = 0;
      this->container_ = nullptr;

      this->size_ = v.size_;
      this->capacity_ = v.capacity_;
      this->container_ = v.container_;

      v.size_ = 0;
      v.capacity_ = 0;
      v.container_ = nullptr;
    }
    return *this;
  }

  ~vector() {
    delete[] this->container_;

    this->size_ = 0;
    this->capacity_ = 0;
    this->container_ = nullptr;
  }

  //-- element access --//
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("index out of range");
    }
    return container_[pos];
  }

  reference operator[](size_type pos) {
    size_type num_zero = 0;
    if (this->size() < pos || num_zero > pos) {
      throw std::out_of_range("Index out of range");
    }
    return container_[pos];
  }

  const_reference front() {
    if (size_ == 0) {
      throw std::out_of_range("FrontError: vector is empty");
    }
    return container_[0];
  }

  const_reference back() {
    if (size_ == 0) {
      throw std::out_of_range("BackError: vector is empty");
    }
    return container_[size_ - 1];
  }

  T *data() { return container_; }

  //-- iterators --//
  iterator begin() { return container_; }
  iterator end() { return container_ + size_; }

  //-- capacity --//
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void reserve(size_type new_capacity) {
    if (new_capacity <= capacity_) return;

    iterator new_container = new value_type[new_capacity];

    for (size_type i = 0; i < size_; ++i) {
      new_container[i] = container_[i];
    }

    delete[] container_;
    container_ = new_container;
    capacity_ = new_capacity;
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    int flag = 0;

    if (size_ == capacity_) {
      flag = 1;
    }

    if (size_ == 0) {
      delete[] container_;
      container_ = nullptr;
      capacity_ = 0;
      flag = 1;
    }
    if (flag == 0) {
      iterator new_container = new value_type[size_];

      for (size_type i = 0; i < size_; ++i) {
        new_container[i] = container_[i];
      }

      delete[] container_;
      container_ = new_container;
      capacity_ = size_;
    }
  }

  //-- modifiers --//
  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - container_;

    if (index > size_) {
      throw std::out_of_range("Index out of range");
    }

    if (size_ == capacity_) {
      size_type new_capacity;
      new_capacity = capacity_ * 2;
      reserve(new_capacity);
    }

    for (size_type i = size_; i > index; --i) {
      container_[i] = container_[i - 1];
    }

    container_[index] = value;
    ++size_;
    return container_ + index;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type index = pos - container_;

    size_type new_size = size_ + sizeof...(args);
    if (new_size > capacity_) {
      reserve(new_size > capacity_ * 2 ? new_size : capacity_ * 2);
      pos = container_ + index;
    }

    for (size_type i = size_; i > index; --i) {
      new (container_ + i - 1 + sizeof...(args))
          T(std::move(container_[i - 1]));
      container_[i - 1].~T();
    }

    iterator result = container_ + index;
    size_type j = 0;

    ((new (container_ + index + j++) T(std::forward<Args>(args))), ...);

    size_ = new_size;

    return result;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), std::forward<Args>(args)...);
  }

  void erase(iterator pos) {
    size_type index = pos - container_;

    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    } else {
      for (size_type i = index; i < size_ - 1; ++i) {
        container_[i] = container_[i + 1];
      }
      --size_;
    }
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      const auto new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }
    container_[size_] = value;
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
      container_[size_].~T();
    }
  }

  void swap(vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(container_, other.container_);
  }

 private:
  // some private fields
  size_type size_;
  size_type capacity_;
  value_type *container_;
};

}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)