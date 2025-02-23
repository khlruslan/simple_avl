#pragma once
#include <algorithm>
#include <cassert>
#include <compare>
#include <cstddef>
#include <ios>      // boolalpha
#include <iostream> //
#include <memory>
#include <utility>
#include <vector>

#define my_debug

namespace adt {

template <class T> bool Intersect(T str1, T end1, T str2, T end2) {
  T str_max = std::max(str1, str2);
  T end_min = std::min(end1, end2);
  return str_max <= end_min;
}
template <class T>
// ADT -  Abstract Data Table
class Adt {
  static constexpr std::size_t kMaxStack = 64;
  static constexpr std::size_t kLeft = 0;
  static constexpr std::size_t kRight = 1;
  static constexpr std::size_t kLeaf = 2;

  using AdtPtr = Adt *;

  struct AvlNode;

  using NodePtr = AvlNode *;
  using NodePtrStack = std::vector<NodePtr>;
  using TraceNode = std::pair<NodePtr, int>;
  using TraceNodeStack = std::vector<TraceNode>;
  using DirectionStack = std::vector<int>;

  struct Tag {
    NodePtr bound_[2] = {nullptr, nullptr}; // child range bounds
    std::size_t count_ = 0;                 // child counter
    void Update(NodePtr node);
  };

  struct AvlNode {
    NodePtr avl_link_[2]; // subtrees
    signed char avl_balance_ = 0;
    T avl_data_;
    Tag tag_;
    AvlNode(T data, AvlNode *left = nullptr, AvlNode *right = nullptr)
        : avl_link_{left, right}, avl_data_(data) {}
    void Update() { tag_.Update(this); }
  };

public:
  class Iterator {
    AdtPtr ptr_ = nullptr;
    bool end_;
    NodePtrStack stack_;

    void ReserveStackCapacity(std::size_t cap = kMaxStack) {
      stack_.reserve(cap);
    }

    Iterator() = delete;

    explicit Iterator(AdtPtr p) : ptr_(p), end_(true) {}

    Iterator(AdtPtr p, NodePtrStack &&stack)
        : ptr_(p), end_(false), stack_(std::move(stack)) {}
    Iterator(AdtPtr p, NodePtr ptr) : ptr_(p), end_(false) {
      ReserveStackCapacity();
      stack_.push_back(ptr);
    }

  public:
    void set(const T &t);
    T &get();

    void dump(std::ostream &os) {
      os << "Iterator to Atd:" << ptr_ << " end: " << std::boolalpha << end_
         << std::noboolalpha << '\n';
      for (const auto &p : stack_) {
        os << "Node :" << p->avl_data_ << '\n';
      }
    }

    bool static is_equal(const Iterator &lhs, const Iterator &rhs) {
      return lhs.ptr_ == rhs.ptr_ && lhs.end_ == rhs.end_;
    }
    bool operator==(const Iterator &rhs) const { return is_equal(*this, rhs); }
    friend class Adt;
  };

  using InsertResult = std::pair<Iterator, bool>;
  using FindResult = Iterator;

public:
  Adt() : end_(this) {}
  std::size_t size() const;
  // Inserts element(s) into the container, if the container doesn't already
  // contain an element with an equivalent key.
  InsertResult probe(const T &t);
  // Inserts element(s) into the container, if the container doesn't already
  // contain an element with an equivalent key.
  InsertResult probe_root(const T &t);
  // Inserts element(s) into the container, if the container doesn't already
  // contain an element with an equivalent key.
  InsertResult insert(const T &t);
  // Removes the element (if one exists) with the key equivalent to key.
  Iterator Erase(const T &t);
  // Removes the element at pos.
  Iterator Erase(Iterator &pos);
  // find node equal key , if not found = return end()
  Iterator find(const T &key);
  // clear Atd
  void Clear();
  // save tree to .dot file
  static void save_dot(std::ostream &os, const Adt &tree);
  // get items vector in preorder traverse
  std::vector<T> GetPreorderVector() const;
  // get items vector in inorder traverse
  std::vector<T> GetInorderVector() const;
  // get vector of avl_balance for all nodes in inorder
  std::vector<int> GetInorderAvlBalanceVector() const;
  // count items in range
  int CountByRange(T first, T second) const;

  Iterator begin() { return end_; }
  Iterator end() { return end_; }
  ~Adt() { Clear(); }

private:
  Iterator end_ = nullptr;
  AvlNode *root_ = nullptr;
  std::size_t size_ = 0ul;

private:
  // In-order traversing tree
  template <class O> void InorderTraverse(NodePtr p, O o) const;
  // Pre-order traversing tree
  template <class O> void PreorderTraverse(NodePtr p, O o) const;
  // Post-order traversing tree
  template <class O> void PostorderTraverse(NodePtr p, O o);
  // Update tags
  void UpdateTags(const NodePtrStack &stack);

  void DumpTraceNodeStack(std::ostream &os, TraceNodeStack &tns);
}; // class Adt

template <class T> std::size_t Adt<T>::size() const { return size_; }
// save tree to .dot file
template <class T> void Adt<T>::save_dot(std::ostream &os, const Adt &tree) {
  os << "digraph Groove{\n";
  os << "  node [shape = record,height = .1];\n";
  // print nodes
  os << "  // all the nodes\n";
  tree.InorderTraverse(tree.root_, [&os](const NodePtr p) {
    if (nullptr == p) {
      return;
    }
    os << "  node" << p->avl_data_ << "[label=\"<f0>|<f2> " << p->avl_data_
       << "\\n"
       << p->tag_.count_ << "\\n [";
    for (int i = 0; i < 2; ++i) {
      if (p->tag_.bound_[i] == nullptr) {
        os << " - ";
      } else {
        os << " " << p->tag_.bound_[i]->avl_data_ << " ";
      }
      if (i == 0) {
        os << " ; ";
      }
    }
    os << "]\\n" << static_cast<int>(p->avl_balance_) << " |<f1>\"];\n";
  });

  // print edges
  os << "  // all the edges\n";
  tree.InorderTraverse(tree.root_, [&os](const NodePtr p) {
    if (nullptr == p) {
      return;
    }
    for (int i = 0; i < 2; ++i) {
      if (nullptr != p->avl_link_[i]) {
        os << "  \"node" << p->avl_data_ << "\":f" << i << " -> \"node"
           << p->avl_link_[i]->avl_data_ << "\":f2;\n";
      }
    }
  });
  os << "}\n";
}

// get items vector in inorder traverse
template <class T> std::vector<T> Adt<T>::GetInorderVector() const {
  std::vector<T> result;
  result.reserve(size());
  InorderTraverse(root_, [&result](const NodePtr p) {
    if (nullptr == p) {
      return;
    }
    result.emplace_back(p->avl_data_);
  });
  return result;
}

// get items vector in preorder traverse
template <class T> std::vector<T> Adt<T>::GetPreorderVector() const {
  std::vector<T> result;
  result.reserve(size());
  PreorderTraverse(root_, [&result](const NodePtr p) {
    if (nullptr == p) {
      return;
    }
    result.emplace_back(p->avl_data_);
  });
  return result;
}

// get vector of avl_balance for all nodes in inorder
template <class T> std::vector<int> Adt<T>::GetInorderAvlBalanceVector() const {
  std::vector<int> result;
  result.reserve(0);
  InorderTraverse(root_, [&result](const NodePtr p) {
    if (nullptr == p) {
      return;
    }
    result.emplace_back(p->avl_balance_);
  });
  return result;
}

// Post-order traverse and free nodes
template <class T>
template <class O>
void Adt<T>::PostorderTraverse(typename Adt<T>::NodePtr node, O o) {
  NodePtr p;
  std::size_t dir;
  TraceNodeStack stack;
  stack.reserve(kMaxStack * 3);
  p = node;
  if (nullptr == node) {
    return;
  }
  stack.emplace_back(p, kLeaf);  // check own node
  stack.emplace_back(p, kRight); // check right link
  stack.emplace_back(p, kLeft);  // check left link

  while (!stack.empty()) {
    TraceNode tp = stack.back();
    p = tp.first;
    dir = tp.second;
    stack.pop_back();
#ifdef my_debug_1
    std::cerr << "Current node:" << p->avl_data_ << " direction :" << dir
              << "\n";
#endif
    if (kLeaf == dir) {
      o(p);
    } else {
      if (nullptr != p->avl_link_[dir]) {
        p = p->avl_link_[dir];
        stack.emplace_back(p, kLeaf);  // check own node
        stack.emplace_back(p, kRight); // check right link
        stack.emplace_back(p, kLeft);  // check left link
      }
    }
  }
}

// Pre-order traverse and free nodes
template <class T>
template <class O>
void Adt<T>::PreorderTraverse(typename Adt<T>::NodePtr node, O o) const {
  NodePtr p;
  std::size_t dir;
  TraceNodeStack stack;
  stack.reserve(kMaxStack * 3);
  p = node;
  if (nullptr == node) {
    return;
  }
  stack.emplace_back(p, kRight); // check right link
  stack.emplace_back(p, kLeft);  // check left link
  stack.emplace_back(p, kLeaf);  // check own node

  while (!stack.empty()) {
    TraceNode tp = stack.back();
    p = tp.first;
    dir = tp.second;
    stack.pop_back();
#ifdef my_debug_1
    std::cerr << "Current node:" << p->avl_data_ << " direction :" << dir
              << "\n";
#endif
    if (kLeaf == dir) {
      o(p);
    } else {
      if (nullptr != p->avl_link_[dir]) {
        p = p->avl_link_[dir];
        stack.emplace_back(p, kRight); // check right link
        stack.emplace_back(p, kLeft);  // check left link
        stack.emplace_back(p, kLeaf);  // check own node
      }
    }
  }
}
//
//
// Clear Avl tree by right rotations and delete root node which has oly right
// child
//
template <class T> void Adt<T>::Clear() {
  NodePtr p, q;
  for (p = root_; nullptr != p; p = q) {
    if (nullptr == p->avl_link_[0]) { // we have only right child
      q = p->avl_link_[1];
      delete p;
    } else {               // rotate right
      q = p->avl_link_[0]; // new root
      p->avl_link_[0] = q->avl_link_[1];
      q->avl_link_[1] = p;
    }
  }
  size_ = 0;
  root_ = nullptr;
}

// In-order traverse and free nodes
template <class T>
template <class O>
void Adt<T>::InorderTraverse(typename Adt<T>::NodePtr node, O o) const {
  NodePtr p;
  std::size_t dir;
  TraceNodeStack stack;
  stack.reserve(kMaxStack * 3);
  p = node;
  if (nullptr == node) {
    return;
  }
  stack.emplace_back(p, kRight); // check right link
  stack.emplace_back(p, kLeaf);  // check own node
  stack.emplace_back(p, kLeft);  // check left link

  while (!stack.empty()) {
    TraceNode tp = stack.back();
    p = tp.first;
    dir = tp.second;
    stack.pop_back();
#ifdef my_debug_1
    std::cerr << "Current node:" << p->avl_data_ << " direction :" << dir
              << "\n";
#endif
    if (kLeaf == dir) {
      o(p);
    } else {
      if (nullptr != p->avl_link_[dir]) {
        p = p->avl_link_[dir];
        stack.emplace_back(p, kRight); // check right link
        stack.emplace_back(p, kLeaf);  // check own node
        stack.emplace_back(p, kLeft);  // check left link
      }
    }
  }
}

template <class T>
void Adt<T>::DumpTraceNodeStack(std::ostream &os,
                                typename Adt<T>::TraceNodeStack &tns) {
  for (const auto &p : tns) {
    os << "Node data:" << p.first->avl_data_ << " direction:" << p.second
       << "\n";
  }
}

template <class T> void Adt<T>::Tag::Update(NodePtr node) {
  if (nullptr == node) {
    count_ = 0;
    bound_[0] = nullptr;
    bound_[1] = nullptr;
    return;
  }
#ifdef my_debug_1
  std::cerr << __FUNCTION__ << " node: " << node->avl_data_ << " count_"
            << count_ << "  ";
#endif
  count_ = 1;
  for (int i = 0; i < 2; ++i) {
    if (node->avl_link_[i] != nullptr) {
      bound_[i] = node->avl_link_[i]->tag_.bound_[i];
      count_ += node->avl_link_[i]->tag_.count_;
#ifdef my_debug_1
      std::cerr << " dir:" << i << " data:" << node->avl_link_[i]->avl_data_
                << " "
                << " count:" << node->avl_link_[i]->tag_.count_ << " ";
#endif
    } else {
      bound_[i] = node;
#ifdef my_debug_1
      std::cerr << " dir:" << i << " data:" << node->avl_data_ << " null ";
#endif
    }
  }
#ifdef my_debug_1
  std::cerr << "final  count_" << count_ << "  "
            << "\n";
#endif
}

// Update Tags in nodes from stack
template <class T> void Adt<T>::UpdateTags(const NodePtrStack &stack) {
  std::for_each(stack.crbegin(), stack.crend(), [](NodePtr p) { p->Update(); });
}
// probe inserts element into the container, if the container doesn't already
// contain an element with an equivalent key.
template <class T> typename Adt<T>::InsertResult Adt<T>::probe(const T &data) {
  NodePtr p, q; // Iterator and parent
  NodePtr y, z; // Top node to update and parent
  NodePtr n;    // new node
  NodePtr w;    // root of rebalanced tree
  DirectionStack da;
  da.reserve(kMaxStack);

  NodePtrStack stack;
  int dir = 0;
  AvlNode dummy(T{}, root_);
  z = &dummy;
  y = root_;

#ifdef my_debug_1
  std::cerr << __FUNCTION__ << " data: " << data << "\n";
#endif
  // Step 1 : Search new node position
  for (q = z, p = y; nullptr != p;
       q = p, stack.push_back(p), p = p->avl_link_[dir]) {
    auto cmp = data <=> p->avl_data_;
    if (cmp == std::strong_ordering::equal) {
      return std::make_pair(Iterator(this, std::move(stack)), false);
    }
    if (p->avl_balance_ !=
        0) { // Keep information about last node need to rebalance
      z = q;
      y = p;
      da.resize(0);
    }
    dir = cmp == std::strong_ordering::greater;
    da.push_back(dir);
  }
  // Step 2 : Insert
  n = new AvlNode(data);
  n->Update();
  ++size_;
  q->avl_link_[dir] = n;

  if (nullptr == y) { // Tree was empty
    root_ = dummy.avl_link_[0];
    return std::make_pair(Iterator(this, root_), false);
  }

  UpdateTags(stack);
  stack.push_back(n);

  // Step 3 : Update balance factor
  int k = 0;
  for (p = y; p != n; p = p->avl_link_[da[k]], ++k) {
    if (da[k] == 0) {
      --(p->avl_balance_);
    } else {
      ++(p->avl_balance_);
    }
  }

  // Step 4 : Rebalance
  if (y->avl_balance_ == -2) {
    // rebalance tree after insertion in left subtree
    NodePtr x = y->avl_link_[0];
    if (x->avl_balance_ == -1) {
      // rotate right at y
      // Test rotate 1
      w = x;
      y->avl_link_[0] = x->avl_link_[1];
      x->avl_link_[1] = y;
      x->avl_balance_ = y->avl_balance_ = 0;
      y->Update();
      w->Update();
    } else {
      // rotate left at x than right at y
      assert(x->avl_balance_ == +1);
      w = x->avl_link_[1];
      x->avl_link_[1] = w->avl_link_[0];
      w->avl_link_[0] = x;
      y->avl_link_[0] = w->avl_link_[1];
      w->avl_link_[1] = y;

      x->Update();
      y->Update();
      w->Update();
      if (w->avl_balance_ == -1) {
        // Test rotate 2
        x->avl_balance_ = 0;
        y->avl_balance_ = +1;
      } else if (w->avl_balance_ == 0) {
        // This means that w is the new node. a, b, c, and d have height 0.
        // After the rotations, x and y have balance factor 0.
        //
        //  Test rotate 4
        //
        x->avl_balance_ = 0;
        y->avl_balance_ = 0;
      } else {
        assert(w->avl_balance_ == 1);
        // Test rotate 3
        x->avl_balance_ = -1;
        y->avl_balance_ = 0;
      }
      w->avl_balance_ = 0;
    }
  } else if (y->avl_balance_ == 2) {
    // rebalance tree after insertion in left subtree
    NodePtr x = y->avl_link_[1];
    if (x->avl_balance_ == 1) {
      // rotate left at y
      // Test rotate 5
      w = x;
      y->avl_link_[1] = x->avl_link_[0];
      x->avl_link_[0] = y;
      x->avl_balance_ = 0;
      y->avl_balance_ = 0;

      y->Update();
      w->Update();
    } else {
      // rotate right at x then left at y
      assert(x->avl_balance_ == -1);
      w = x->avl_link_[0];
      x->avl_link_[0] = w->avl_link_[1];
      w->avl_link_[1] = x;
      y->avl_link_[1] = w->avl_link_[0];
      w->avl_link_[0] = y;

      x->Update();
      y->Update();
      w->Update();
      if (w->avl_balance_ == 1) {
        // Test rotate 6
        x->avl_balance_ = 0;
        y->avl_balance_ = -1;
      } else if (w->avl_balance_ == 0) {
        // This means that w is the new node. a, b, c, and d have height 0.
        // After the rotations, x and y have balance factor 0. Test rotate 7
        x->avl_balance_ = 0;
        y->avl_balance_ = 0;
      } else {
        // Test rotate 8
        assert(w->avl_balance_ == -1);
        x->avl_balance_ = 1;
        y->avl_balance_ = 0;
      }
      w->avl_balance_ = 0;
    }
  } else { // no need to rebalance tree . stack contains all nodes to inserted
           // node
    root_ = dummy.avl_link_[0];
    return std::make_pair(Iterator(this, std::move(stack)), false);
  }
  // connect rebalanced tree to parent node z
  z->avl_link_[y != z->avl_link_[0]] = w;
  root_ = dummy.avl_link_[0];

  // Step 5  erase last items in stack
  if (z != &dummy) {
    while (!stack.empty() && stack.back() != z) {
      stack.pop_back();
    }
  }
  assert(z == &dummy || stack.back() == z);

  // Add required nodes to iterator
  p = w;
  while (nullptr != p) {
    stack.push_back(p);
    auto cmp = data <=> p->avl_data_;
    if (cmp == std::strong_ordering::equal) {
      p = nullptr;
    } else {
      dir = cmp == std::strong_ordering::greater;
      p = p->avl_link_[dir];
    }
  }

  return std::make_pair(Iterator(this, std::move(stack)), false);
}

// Inserts element into the container, if the container doesn't already contain
// an element with an equivalent key.
template <class T> typename Adt<T>::InsertResult Adt<T>::insert(const T &data) {
  return probe(data);
}

// find node equal key , if not found = return end()
template <class T> typename Adt<T>::Iterator Adt<T>::find(const T &data) {
  NodePtrStack stack;
  stack.reserve(kMaxStack);

  for (NodePtr p = root_; p != nullptr;) {
    auto cmp = data <=> p->avl_data_;
    stack.push_back(p);
    if (cmp < 0) {
      p = p->avl_link_[0];
    } else if (cmp > 0) {
      p = p->avl_link_[1];
    } else {
      return {this, std::move(stack)};
    }
  }
  return end();
}

// count items in range
template <class T> int Adt<T>::CountByRange(T first, T second) const {
#ifdef my_debug_1
  std::cerr << __FUNCTION__ << " first:" << first << " , "
            << "second:" << second << "\n";
#endif
  if (first > second) {
    return 0;
  }
  if (size() == 0) {
    return 0;
  }

  NodePtr p;
  int result = 0;
  NodePtrStack stack;
  stack.reserve(kMaxStack * 3);
  p = root_;
  T n_first;
  T n_second;

  stack.emplace_back(p); // check child node

  while (!stack.empty()) {
    p = stack.back();
    stack.pop_back();
#ifdef my_debug_1
    std::cerr << "Current node:" << p->avl_data_ << "\n";
#endif
    n_first = p->tag_.bound_[0]->avl_data_;
    n_second = p->tag_.bound_[1]->avl_data_;

    if (first <= n_first && n_second <= second) {
      result += p->tag_.count_;
    } else if (Intersect(first, second, n_first, n_second)) {
      if (first <= p->avl_data_ && p->avl_data_ <= second) {
        ++result;
      }
      for (int i = 0; i < 2; ++i) {
        if (nullptr != p->avl_link_[i])
          stack.emplace_back(p->avl_link_[i]); // check child node
      }
    }
  }

  return result;
}

} // namespace adt
