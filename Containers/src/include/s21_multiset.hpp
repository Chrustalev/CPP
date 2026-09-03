#pragma once

#include <functional>        // for less
#include <initializer_list>  // for initializer_list
#include <utility>           // for pair

#include "detail/rb_tree.hpp"
#include "s21_vector.hpp"

// см. /CPP2_s21_containers/materials/containers_info_extra_rus.md
// см. https://en.cppreference.com/w/cpp/container/multiset.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {

template <typename Key>
class multiset {
 private:
  using Rb_tree_ = RbTree<Key, Identity<Key>, std::less<Key>>;

 public:
  //-- member type --//
  using key_type = Rb_tree_::key_type;
  using value_type = Rb_tree_::key_type;
  using reference = Rb_tree_::reference;
  using const_reference = Rb_tree_::const_reference;
  using iterator = Rb_tree_::const_iterator;
  using const_iterator = Rb_tree_::const_iterator;
  using size_type = Rb_tree_::size_type;

  //-- member functions --//
  multiset() = default;
  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) _M_tree_.insert_equal(item);
  }

  DEFAULTED_FIVE(multiset);

  //-- iterators --//
  iterator begin() { return _M_tree_.begin(); }
  const_iterator begin() const { return _M_tree_.begin(); }
  const_iterator cbegin() const noexcept { return _M_tree_.cbegin(); }

  iterator end() { return _M_tree_.end(); }
  const_iterator end() const { return _M_tree_.end(); }
  const_iterator cend() const noexcept { return _M_tree_.end(); }

  //-- capacity --//
  bool empty() const noexcept { return _M_tree_.empty(); }
  size_type size() const { return _M_tree_.size(); }
  size_type max_size() const { return _M_tree_.max_size(); }

  //-- modifiers --//
  void clear() noexcept { _M_tree_.clear(); }

  iterator insert(const value_type &value) {
    return _M_tree_.insert_equal(value);
  }

  template <typename... Args>
  s21::vector<iterator> insert_many(Args &&...args) {
    s21::vector<iterator> results;

    size_t count = sizeof...(args);
    results.reserve(count);

    ((results.push_back(_M_tree_.insert_equal(std::forward<Args>(args)))), ...);

    return results;
  }

  void erase(iterator pos) { _M_tree_.erase(pos); }

  void swap(multiset &other) noexcept { _M_tree_.swap(other._M_tree_); }

  void merge(multiset &other) {
    for (auto it = other.begin(); it != other.end();) {
      _M_tree_.insert_equal(*it);

      auto to_erase = it++;
      other.erase(to_erase);
    }
  }

  //-- lookup --//
  size_type count(const key_type &key) { return _M_tree_.count(key); }

  iterator find(const key_type &key) { return _M_tree_.find(key); }
  const_iterator find(const key_type &key) const { return _M_tree_.find(key); }

  bool contains(const key_type &key) const {
    return _M_tree_.find(key) != _M_tree_.end();
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return _M_tree_.equal_range(key);
  }

  iterator lower_bound(const key_type &key) {
    return _M_tree_.lower_bound(key);
  }

  iterator upper_bound(const key_type &key) {
    return _M_tree_.upper_bound(key);
  }

 private:
  // some private fields
  Rb_tree_ _M_tree_;
};

}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)