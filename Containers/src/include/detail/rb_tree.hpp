#pragma once

#include <cstddef>
#include <functional>
#include <limits>
#include <utility>

#include "utils.hpp"

// см. /CPP2_s21_containers/materials/instructions_for_testing_rus.md

// NOLINTBEGIN(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)

template <typename T>
struct Identity {
  using type = T;
  const T &operator()(const T &x) const { return x; }
};

template <typename K, typename V>
struct SelectFirst {
  using type = K;
  template <typename PairType>
  const K &operator()(const PairType &p) const {
    return p.first;
  }
};

template <typename Value, typename KeyExtract, typename Compare = std::less<>>
class RbTree {
 private:
  struct NodeBase {
    using NodeBasePtr = NodeBase *;

    enum class Color { RED, BLACK };

    NodeBase(NodeBasePtr p, NodeBasePtr l, NodeBasePtr r)
        : parent(p), left(l), right(r) {}

    virtual ~NodeBase() = default;

    static NodeBasePtr make_nil() {
      NodeBasePtr nil = new NodeBase(nullptr, nullptr, nullptr);
      nil->color = Color::BLACK;
      return nil;
    }

    Color color = Color::RED;
    NodeBasePtr parent = nullptr;
    NodeBasePtr left = nullptr;
    NodeBasePtr right = nullptr;
  };

  struct DataNode : public NodeBase {
    using DataNodePtr = DataNode *;

    Value value;
    DataNode(const Value &v, NodeBase *p, NodeBase *l, NodeBase *r)
        : NodeBase(p, l, r), value(v) {}
  };

  template <bool IsConst>
  class RbTreeIterator {
    template <typename V, typename KE, typename C>
    friend class RbTree;

   public:
    using value_type = std::conditional_t<IsConst, const Value, Value>;
    using pointer = value_type *;
    using reference = value_type &;
    // for stl
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

   private:
    using NodePtr = std::conditional_t<IsConst, const NodeBase *, NodeBase *>;
    using DataNodePtr =
        std::conditional_t<IsConst, const DataNode *, DataNode *>;

    NodePtr node_;
    NodePtr nil_;
    NodePtr root_;

   public:
    // конструкторы
    RbTreeIterator() : node_(nullptr), nil_(nullptr), root_(nullptr) {}

    RbTreeIterator(NodePtr node, NodePtr nil, NodePtr root)
        : node_(node), nil_(nil), root_(root) {}

    // iterator -> const_iterator
    template <bool OtherIsConst,
              typename = std::enable_if_t<IsConst && !OtherIsConst>>
    RbTreeIterator(const RbTreeIterator<OtherIsConst> &other)
        : node_(other.node_), nil_(other.nil_), root_(other.root_) {}

    reference operator*() const {
      return static_cast<DataNodePtr>(node_)->value;
    }

    pointer operator->() const {
      return &static_cast<DataNodePtr>(node_)->value;
    }

    RbTreeIterator &operator++() {
      node_ = NodePtr(RbTree::successor(node_, nil_));
      return *this;
    }

    RbTreeIterator operator++(int) {
      RbTreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    RbTreeIterator &operator--() {
      if (node_ == nil_) {
        // --end() -> maximum всего дерева
        if (root_ == nil_) return *this;
        node_ = RbTree::maximum(root_, nil_);
      } else {
        node_ = RbTree::predecessor(node_, nil_, root_);
      }
      return *this;
    }

    RbTreeIterator operator--(int) {
      RbTreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    template <bool OtherIsConst>
    bool operator==(const RbTreeIterator<OtherIsConst> &other) const {
      return node_ == other.node_;
    }

    template <bool OtherIsConst>
    bool operator!=(const RbTreeIterator<OtherIsConst> &other) const {
      return !(*this == other);
    }

    // for debug
   private:
    NodePtr base() const { return node_; }
    NodePtr nil() const { return nil_; }
    NodePtr root() const { return root_; }
  };

 public:
  using key_type = typename KeyExtract::type;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RbTreeIterator<false>;
  using const_iterator = RbTreeIterator<true>;
  using size_type = size_t;

  RbTree()
      : nil_{NodeBase::make_nil()},
        root_{nil_},
        size_(0),
        key_extract_{},
        compare_{} {}

  RbTree(const RbTree &other)
      : nil_(NodeBase::make_nil()),
        root_(nil_),
        size_(0),
        key_extract_(other.key_extract_),
        compare_(other.compare_) {
    try {
      if (other.root_ != other.nil_) {
        root_ = copy_subtree(other.root_, other.nil_, nil_);
        size_ = other.size_;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  RbTree(RbTree &&other) noexcept
      : nil_(other.nil_),
        root_(other.root_),
        size_(other.size_),
        key_extract_(std::move(other.key_extract_)),
        compare_(std::move(other.compare_)) {
    other.nil_ = NodeBase::make_nil();
    other.root_ = other.nil_;
    other.size_ = 0;
  }

  RbTree &operator=(const RbTree &other) {
    if (this == &other) return *this;

    RbTree temp(other);
    swap(temp);
    return *this;
  }

  RbTree &operator=(RbTree &&other) noexcept {
    if (this == &other) return *this;

    clear();
    delete nil_;

    nil_ = other.nil_;
    root_ = other.root_;
    size_ = other.size_;
    key_extract_ = std::move(other.key_extract_);
    compare_ = std::move(other.compare_);

    other.nil_ = NodeBase::make_nil();
    other.root_ = other.nil_;
    other.size_ = 0;

    return *this;
  }

  ~RbTree() {
    clear();

    if (nil_ != nullptr) {
      delete nil_;
      nil_ = nullptr;
    }
  }

  //--- public methods ---//
  //-- iterators --//
  iterator begin() {
    if (empty()) return end();
    return iterator(minimum(root_, nil_), nil_, root_);
  }

  const_iterator begin() const {
    if (empty()) return end();
    return const_iterator(minimum(root_, nil_), nil_, root_);
  }

  const_iterator cbegin() const { return begin(); }

  iterator end() { return iterator(nil_, nil_, root_); }

  const_iterator end() const { return const_iterator(nil_, nil_, root_); }

  const_iterator cend() const { return end(); }

  //-- modifiers --//
  iterator insert_equal(const Value &value) {
    NodeBase *z = create_node(value);
    NodeBase *y = nil_;
    NodeBase *x = root_;

    while (x != nil_) {
      y = x;
      const key_type &val_key = key_extract_(value);
      const key_type &x_key = key_extract_(static_cast<DataNode *>(x)->value);

      if (compare_(val_key, x_key)) {
        x = x->left;
      } else {
        // при равных ключах уходим направо
        x = x->right;
      }
    }

    z->parent = y;
    if (y == nil_) {
      root_ = z;
    } else if (compare_(key_extract_(value),
                        key_extract_(static_cast<DataNode *>(y)->value))) {
      y->left = z;
    } else {
      y->right = z;
    }

    z->left = z->right = nil_;
    insert_fixup(z);

    ++size_;
    return iterator(z, nil_, root_);
  }

  std::pair<iterator, bool> insert_unique(const Value &value) {
    NodeBase *z = create_node(value);
    NodeBase *y = nil_;
    NodeBase *x = root_;

    while (x != nil_) {
      y = x;
      const key_type &val_key = key_extract_(value);
      const key_type &x_key = key_extract_(static_cast<DataNode *>(x)->value);

      if (compare_(val_key, x_key)) {
        x = x->left;
      } else if (compare_(x_key, val_key)) {
        x = x->right;
      } else {
        // ключ уже добавлен
        destroy_node(z);
        return {iterator(x, nil_, root_), false};
      }
    }

    z->parent = y;
    if (y == nil_) {
      root_ = z;
    } else if (compare_(key_extract_(value),
                        key_extract_(static_cast<DataNode *>(y)->value))) {
      y->left = z;
    } else {
      y->right = z;
    }

    z->left = z->right = nil_;
    insert_fixup(z);

    ++size_;
    return {iterator(z, nil_, root_), true};
  }

  iterator erase(iterator position) {
    _CUSTOM_ASSERT(position != end(), "cannot erase end iterator");

    iterator next = position;
    ++next;

    NodeBase *node_to_delete = position.base();
    rb_delete(node_to_delete);
    destroy_node(node_to_delete);
    --size_;

    return iterator{next};
  }

  iterator erase(const_iterator position) {
    _CUSTOM_ASSERT(position != end(), "cannot erase end iterator");

    NodeBase *node = const_cast<NodeBase *>(position.node_);
    NodeBase *nil = const_cast<NodeBase *>(position.nil_);
    NodeBase *root = const_cast<NodeBase *>(position.root_);

    iterator non_const_iter(node, nil, root);
    return erase(non_const_iter);
  }

  size_type erase(const key_type &key) {
    iterator it = find(key);
    if (it == end()) return 0;

    erase(it);
    return 1;
  }

  iterator erase(iterator first, iterator last) {
    while (first != last) {
      first = erase(first);
    }
    return last;
  }

  void clear() {
    clear_subtree(root_);
    root_ = nil_;
    size_ = 0;
  }

  void swap(RbTree &other) {
    std::swap(nil_, other.nil_);
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(key_extract_, other.key_extract_);
    std::swap(compare_, other.compare_);
  }

  //-- capacity --//
  bool empty() const { return nil_ == root_; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(DataNode);
  }

  //-- find --//
  iterator find(const key_type &key) {
    NodeBase *node = root_;

    while (node != nil_) {
      const key_type &current_key =
          key_extract_(static_cast<DataNode *>(node)->value);

      if (compare_(key, current_key)) {
        node = node->left;
      } else if (compare_(current_key, key)) {
        node = node->right;
      } else {
        return iterator(node, nil_, root_);
      }
    }

    return end();
  }

  const_iterator find(const key_type &key) const {
    const NodeBase *node = root_;

    while (node != nil_) {
      const key_type &current_key =
          key_extract_(static_cast<const DataNode *>(node)->value);

      if (compare_(key, current_key)) {
        node = node->left;
      } else if (compare_(current_key, key)) {
        node = node->right;
      } else {
        return const_iterator(node, nil_, root_);
      }
    }

    return end();
  }

  iterator lower_bound(const key_type &key) {
    return iterator(lower_bound_node(key), nil_, root_);
  }

  const_iterator lower_bound(const key_type &key) const {
    return const_iterator(lower_bound_node(key), nil_, root_);
  }

  iterator upper_bound(const key_type &key) {
    return iterator(upper_bound_node(key), nil_, root_);
  }

  const_iterator upper_bound(const key_type &key) const {
    return const_iterator(upper_bound_node(key), nil_, root_);
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return {lower_bound(key), upper_bound(key)};
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &key) const {
    return {lower_bound(key), upper_bound(key)};
  }

  size_type count(const key_type &key) const {
    auto range = equal_range(key);
    size_type cnt = 0;
    for (auto it = range.first; it != range.second; ++it) {
      ++cnt;
    }
    return cnt;
  }

 private:
  //-- private methods --//
  static decltype(auto) minimum(auto x, auto nil) {
    while (x->left != nil) {
      x = x->left;
    }
    return x;
  }

  static decltype(auto) maximum(auto x, auto nil) {
    while (x->right != nil) {
      x = x->right;
    }
    return x;
  }

  // следующий элемент за переданным
  static decltype(auto) successor(auto x, auto nil) {
    using XType = decltype(x);

    if (x->right != nil) return minimum(static_cast<XType>(x->right), nil);

    auto y = x->parent;
    while (y != nil && x == y->right) {
      x = y;
      y = y->parent;
    }
    return static_cast<XType>(y);
    // return y;
  }

  // предыдущий элемент от переданного
  static decltype(auto) predecessor(auto x, auto nil, auto root) {
    if (x == nil) {
      return maximum(root, nil);
    }

    using XType = decltype(x);
    if (x->left != nil) return maximum(static_cast<XType>(x->left), nil);

    auto y = x->parent;
    while (y != nil && x == y->left) {
      x = y;
      y = y->parent;
    }
    return static_cast<XType>(y);
  }

  void left_rotate(NodeBase *x) {
    auto y = x->right;
    x->right = y->left;

    if (y->left != nil_) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == nil_)
      root_ = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void right_rotate(NodeBase *y) {
    auto x = y->left;
    y->left = x->right;

    if (x->right != nil_) x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == nil_)
      root_ = x;
    else if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;

    x->right = y;
    y->parent = x;
  }

  // замена поддеревьев
  void transplant(NodeBase *u, NodeBase *v) {
    if (u->parent == nil_)
      root_ = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;

    if (v != nil_) v->parent = u->parent;
  }

  void insert_fixup(NodeBase *z) {
    while (z->parent->color == NodeBase::Color::RED) {
      if (z->parent == z->parent->parent->left) {
        NodeBase *y = z->parent->parent->right;  // дядя

        if (y->color == NodeBase::Color::RED) {
          // случай 1; дядя красный
          z->parent->color = NodeBase::Color::BLACK;
          y->color = NodeBase::Color::BLACK;
          z->parent->parent->color = NodeBase::Color::RED;
          z = z->parent->parent;
        } else {
          // дядя черный
          if (z == z->parent->right) {
            // случай 2:
            z = z->parent;
            left_rotate(z);
          }
          // случай 3:
          z->parent->color = NodeBase::Color::BLACK;
          z->parent->parent->color = NodeBase::Color::RED;
          right_rotate(z->parent->parent);
        }
      } else {
        // симметрично: родитель z - правый ребенок
        NodeBase *y = z->parent->parent->left;  // Дядя

        if (y->color == NodeBase::Color::RED) {
          // случай 1; дядя красный
          z->parent->color = NodeBase::Color::BLACK;
          y->color = NodeBase::Color::BLACK;
          z->parent->parent->color = NodeBase::Color::RED;
          z = z->parent->parent;
        } else {
          // дядя черный
          if (z == z->parent->left) {
            // случай 2
            z = z->parent;
            right_rotate(z);
          }
          // случай 3
          z->parent->color = NodeBase::Color::BLACK;
          z->parent->parent->color = NodeBase::Color::RED;
          left_rotate(z->parent->parent);
        }
      }
    }
    root_->color = NodeBase::Color::BLACK;
  }

  NodeBase *rb_delete(NodeBase *z) {
    NodeBase *y = z;
    NodeBase *x = nullptr;
    NodeBase *x_parent = nullptr;

    typename NodeBase::Color y_original_color = y->color;

    if (z->left == nil_) {
      // случай 1
      x = z->right;
      transplant(z, z->right);
      x_parent = z->parent;
    } else if (z->right == nil_) {
      // случай 2
      x = z->left;
      transplant(z, z->left);
      x_parent = z->parent;
    } else {
      // случай 3
      y = minimum(z->right, nil_);  // преемник
      y_original_color = y->color;
      x = y->right;

      if (y->parent == z) {
        if (x != nil_) {
          x->parent = y;
        }
        x_parent = y;
      } else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
        x_parent = y->parent;
      }

      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }

    if (y_original_color == NodeBase::Color::BLACK) {
      delete_fixup(x, x_parent);
    }

    return z;  // Возвращаем удаленный узел (потом нужно destroy)
  }

  void delete_fixup(NodeBase *x, NodeBase *x_parent) {
    // x может быть nil, поэтому храним родителя отдельно
    while (x != root_ && (x == nil_ || x->color == NodeBase::Color::BLACK)) {
      if (x == (x_parent ? x_parent->left : nil_)) {
        NodeBase *w = x_parent->right;

        if (w->color == NodeBase::Color::RED) {
          // случай 1
          w->color = NodeBase::Color::BLACK;
          x_parent->color = NodeBase::Color::RED;
          left_rotate(x_parent);
          w = x_parent->right;
        }

        if ((w->left == nil_ || w->left->color == NodeBase::Color::BLACK) &&
            (w->right == nil_ || w->right->color == NodeBase::Color::BLACK)) {
          // случай 2
          w->color = NodeBase::Color::RED;
          x = x_parent;
          x_parent = x->parent;
        } else {
          if (w->right == nil_ || w->right->color == NodeBase::Color::BLACK) {
            // случай 3
            if (w->left != nil_) {
              w->left->color = NodeBase::Color::BLACK;
            }
            w->color = NodeBase::Color::RED;
            right_rotate(w);
            w = x_parent->right;
          }
          // случай 4
          w->color = x_parent->color;
          x_parent->color = NodeBase::Color::BLACK;
          if (w->right != nil_) {
            w->right->color = NodeBase::Color::BLACK;
          }
          left_rotate(x_parent);
          x = root_;
        }
      } else {
        NodeBase *w = x_parent->left;

        if (w->color == NodeBase::Color::RED) {
          w->color = NodeBase::Color::BLACK;
          x_parent->color = NodeBase::Color::RED;
          right_rotate(x_parent);
          w = x_parent->left;
        }

        if ((w->right == nil_ || w->right->color == NodeBase::Color::BLACK) &&
            (w->left == nil_ || w->left->color == NodeBase::Color::BLACK)) {
          w->color = NodeBase::Color::RED;
          x = x_parent;
          x_parent = x->parent;
        } else {
          if (w->left == nil_ || w->left->color == NodeBase::Color::BLACK) {
            if (w->right != nil_) {
              w->right->color = NodeBase::Color::BLACK;
            }
            w->color = NodeBase::Color::RED;
            left_rotate(w);
            w = x_parent->left;
          }
          w->color = x_parent->color;
          x_parent->color = NodeBase::Color::BLACK;
          if (w->left != nil_) {
            w->left->color = NodeBase::Color::BLACK;
          }
          right_rotate(x_parent);
          x = root_;
        }
      }
    }

    if (x != nil_) {
      x->color = NodeBase::Color::BLACK;
    }
  }

  NodeBase *create_node(const Value &value) {
    DataNode *node = new DataNode(value, nil_, nil_, nil_);
    return static_cast<NodeBase *>(node);
  }

  void destroy_node(NodeBase *node) {
    if (!node || node == nil_) return;

    delete static_cast<DataNode *>(node);
  }

  NodeBase *copy_subtree(NodeBase *other_node, NodeBase *other_nil,
                         NodeBase *this_nil) {
    if (other_node == other_nil) {
      return this_nil;
    }

    NodeBase *new_node = nullptr;
    try {
      new_node = create_node(static_cast<DataNode *>(other_node)->value);

      new_node->left = this_nil;
      new_node->right = this_nil;
      new_node->color = other_node->color;

      // левое поддерево
      new_node->left = copy_subtree(other_node->left, other_nil, this_nil);
      if (new_node->left != this_nil) {
        new_node->left->parent = new_node;
      }

      // правое поддерево
      new_node->right = copy_subtree(other_node->right, other_nil, this_nil);
      if (new_node->right != this_nil) {
        new_node->right->parent = new_node;
      }

    } catch (...) {
      if (new_node) {
        destroy_node(new_node);
      }
      throw;
    }

    return new_node;
  }

  void clear_subtree(NodeBase *node) {
    if (node == nil_) return;

    clear_subtree(node->left);
    clear_subtree(node->right);
    destroy_node(node);
  }

  NodeBase *find_node(const key_type &key) const {
    NodeBase *current = root_;

    while (current != nil_) {
      const key_type &current_key =
          key_extract_(static_cast<const DataNode *>(current)->value);

      if (compare_(key, current_key))  // ключ поиска меньше
        current = current->left;
      else if (compare_(current_key, key))  // ключ поиска больше
        current = current->right;
      else
        return current;  // найдено
    }

    return nil_;  // не найдено
  }

  NodeBase *lower_bound_node(const key_type &key) const {
    NodeBase *current = root_;
    NodeBase *result = nil_;

    while (current != nil_) {
      const key_type &current_key =
          key_extract_(static_cast<const DataNode *>(current)->value);

      if (!compare_(current_key, key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return result;
  }

  NodeBase *upper_bound_node(const key_type &key) const {
    NodeBase *current = root_;
    NodeBase *result = nil_;

    while (current != nil_) {
      const key_type &current_key =
          key_extract_(static_cast<const DataNode *>(current)->value);

      if (compare_(key, current_key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return result;
  }

  //-- private fields --//
  NodeBase::NodeBasePtr nil_;
  NodeBase::NodeBasePtr root_;
  size_type size_;

  KeyExtract key_extract_;
  Compare compare_;
};

// NOLINTEND(cppcoreguidelines-special-member-functions,
// readability-identifier-naming)