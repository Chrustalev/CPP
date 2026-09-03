#pragma once

#include <functional>        // for less
#include <initializer_list>  // for initializer_list
#include <stdexcept>         // for out_of_range
#include <utility>           // for pair

#include "detail/rb_tree.hpp"
#include "s21_vector.hpp"

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md
// см. https://en.cppreference.com/w/cpp/container/map.html

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

namespace s21 {

template <typename Key, typename T>
class map {
 private:
  using Rb_tree_ =
      RbTree<std::pair<const Key, T>, SelectFirst<Key, T>, std::less<Key>>;

 public:
  //-- member type --//
  using key_type = Rb_tree_::key_type;
  using mapped_type = T;
  using value_type = Rb_tree_::value_type;
  using reference = Rb_tree_::reference;
  using const_reference = Rb_tree_::const_reference;
  using iterator = Rb_tree_::iterator;
  using const_iterator = Rb_tree_::const_iterator;
  using size_type = Rb_tree_::size_type;

  //-- member functions --//
  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) _M_tree_.insert_unique(item);
  }

  DEFAULTED_FIVE(map);

  //-- element access --//
  mapped_type &at(const Key &key) {
    auto it = _M_tree_.find(key);
    if (it == _M_tree_.end()) throw std::out_of_range("map::at: key not found");
    return (*it).second;
  }

  const mapped_type &at(const Key &key) const {
    auto it = _M_tree_.find(key);
    if (it == _M_tree_.end()) throw std::out_of_range("map::at: key not found");
    return (*it).second;
  }

  mapped_type &operator[](const Key &key) {
    auto it = _M_tree_.find(key);
    if (it == _M_tree_.end())
      return (*_M_tree_.insert_unique(value_type{key, mapped_type{}}).first)
          .second;
    return (*it).second;
  }

  //-- iterators --//
  iterator begin() { return _M_tree_.begin(); }
  const_iterator begin() const { return _M_tree_.begin(); }
  const_iterator cbegin() const noexcept { return _M_tree_.cbegin(); }

  iterator end() { return _M_tree_.end(); }
  const_iterator end() const { return _M_tree_.end(); }
  const_iterator cend() const noexcept { return _M_tree_.cend(); }

  //-- capacity --//
  bool empty() const noexcept { return _M_tree_.empty(); }
  size_type size() const { return _M_tree_.size(); }
  size_type max_size() const { return _M_tree_.max_size(); }

  //-- modifiers --//
  void clear() noexcept { _M_tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return _M_tree_.insert_unique(value);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    return _M_tree_.insert_unique(value_type{key, obj});
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;

    size_t count = sizeof...(args);
    results.reserve(count);

    ((results.push_back(_M_tree_.insert_unique(std::forward<Args>(args)))),
     ...);

    return results;
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    auto result = _M_tree_.insert_unique(value_type{key, obj});
    if (!result.second) {
      result.first->second = obj;
    }
    return result;
  }

  void erase(iterator pos) { _M_tree_.erase(pos); }
  void swap(map &other) noexcept { _M_tree_.swap(other._M_tree_); }

  void merge(map &other) {
    for (auto it = other.begin(); it != other.end();) {
      auto res = _M_tree_.insert_unique(*it);
      if (res.second) {
        auto to_erase = it++;
        other.erase(to_erase);
      } else {
        ++it;
      }
    }
  }

  //-- lookup --//
  iterator find(const Key &key) { return _M_tree_.find(key); }
  const_iterator find(const Key &key) const { return _M_tree_.find(key); }

  bool contains(const Key &key) const {
    return _M_tree_.find(key) != _M_tree_.end();
  }

 private:
  // some private fields
  Rb_tree_ _M_tree_;
};

}  // namespace s21

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)