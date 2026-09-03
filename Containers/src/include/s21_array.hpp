#pragma once

#include <algorithm>         // for copy
#include <cstddef>           // for size_t
#include <initializer_list>  // for initializer_list
#include <stdexcept>         // for out_of_range
#include <utility>           // for move

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/array.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = size_t;

  //-- member functions --//
  array() : m_size_{N} {}

  array(std::initializer_list<value_type> const &items) : m_size_{N} {
    std::copy(items.begin(), items.end(), data_);
  }

  array(const array &a) : m_size_{N} { std::copy(a.data_, a.data_ + N, data_); }

  array(array &&a) noexcept : m_size_{N} {
    if (&a == this) return;
    std::move(a.data_, a.data_ + N, data_);
    a.m_size_ = 0;
  }

  array &operator=(const array &a) {
    if (&a == this) return *this;
    m_size_ = N;
    std::copy(a.data_, a.data_ + N, data_);
    return *this;
  }

  array &operator=(array &&a) noexcept {
    if (&a == this) return *this;
    m_size_ = N;
    std::move(a.data_, a.data_ + N, data_);
    return *this;
  }

  ~array() { m_size_ = 0; }

  //-- element access --//
  reference at(size_type pos) {
    if (pos >= size()) throw std::out_of_range("Index out of range");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front() const { return data_[0]; }

  const_reference back() const { return data_[m_size_ - 1]; }

  iterator data() noexcept { return data_; }

  //-- iterators --//
  iterator begin() noexcept { return data(); }
  iterator end() noexcept { return data() + m_size_; }

  //-- capacity --//
  bool empty() const noexcept { return m_size_ == 0; }
  size_type size() const noexcept { return m_size_; }
  size_type max_size() const noexcept { return size(); }

  //-- modifiers --//
  void swap(array &other) noexcept {
    if (&other == this) return;
    for (size_t i = 0; i < m_size_; i++) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void fill(const_reference value) {
    for (size_t i = 0; i < m_size_; i++) data_[i] = value;
  }

 private:
  // some private fields
  size_t m_size_;
  value_type data_[N];
};
}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)