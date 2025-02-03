#pragma once
#include <cstddef>
#include <memory>
#include <utility>
#include <ios> // boolalpha
#include <iostream> // 
#include <vector>


namespace adt{
template <class T>
  // ADT -  Abstract Data Table
  class Adt{
      static constexpr std::size_t kMaxStack = 64;
      using AdtPtr = Adt*;

      struct AvlNode;
      using NodePtr = AvlNode*;
      using NodePtrStack = std::vector<NodePtr>;
      using TraceNode = std::pair<NodePtr, int>;
      using TraceNodeStack = std::vector<TraceNode>;

      struct AvlNode{
        NodePtr avl_link_[2]; // subtrees
        signed char avl_balance_ = 0;
        T avl_data_;
        AvlNode(T data, AvlNode *left = nullptr, AvlNode *right = nullptr)
          :avl_link_{left, right}, avl_data_(data) {
        }
      };

    public:
      class Iterator{
        AdtPtr ptr_ = nullptr;
        bool end_;
        NodePtrStack stack_;
        
        void ReserveStackCapacity(std::size_t cap = kMaxStack){
          stack_.reserve(cap);
        }

        Iterator() = delete;

        explicit Iterator(AdtPtr p): ptr_(p), end_(true) {
        }
       
        Iterator(AdtPtr p, NodePtrStack&&  stack): ptr_(p), end_(false), stack_(std::move(stack)) {
        }
        Iterator(AdtPtr p, NodePtr ptr): ptr_(p), end_(false) {
          ReserveStackCapacity();
          stack_.push_back(ptr);
        }
        public:
        void set(const T& t);
        T& get();

        void dump(std::ostream& os){
          os << "Iterator to Atd:" << ptr_ << " end: " << std::boolalpha<< end_ << std::noboolalpha << '\n';
          for (const auto& p : stack_){
          os <<"Node :" << p->avl_data_ << '\n';
          }
        }

        bool static is_equal(const Iterator& lhs, const Iterator& rhs){
          return lhs.ptr_ == rhs.ptr_ && lhs.end_ == rhs.end_;
        }
        bool operator==(const Iterator& rhs) const{
          return is_equal(*this, rhs);
        }
        friend class Adt;
      };

      using InsertResult = std::pair<Iterator, bool>;
      using FindResult = Iterator;

    public:
      Adt():end_(this) {}
      std::size_t size() const;
      //Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
      InsertResult probe(const T& t);
      //Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
      InsertResult probe_root(const T& t);
      //Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
      InsertResult insert(const T& t);
      // Removes the element (if one exists) with the key equivalent to key.
      Iterator erase(const T& t);
      // Removes the element at pos.
      Iterator erase(Iterator& pos);
      // find node equal key , if not found = return end()
      Iterator find(const T& key);
      // save tree to .dot file 
      static void save_dot(std::ostream& os, const Adt& tree);

      Iterator begin() {return end_;}
      Iterator end() {return end_;}
    private:
      Iterator end_ = nullptr;
      AvlNode* root_;
      std::size_t size_ = 0ul;
    private:
      // inorder traversing tree
      template <class O>
       void InorderTraverse(const NodePtr p, O o) const; 

  }; //class Adt

// save tree to .dot file 
template <class T>
void Adt<T>::save_dot(std::ostream& os, const Adt& tree) {
  os << "digraph Groove{\n";
  os << "  node [shape = record,height = .1];\n";
  // print nodes
  os << "  // all the nodes\n";
  tree.InorderTraverse(tree.root_, [&os](const NodePtr p){
     if (nullptr == p){
     return;
     }
     os << "  node"<< p->avl_data_ << "[label=\"<f0>|<f2> " << p->avl_data_ << " |<f1>\"];\n";
  });

  // print edges
  os << "  // all the edges\n";
  tree.InorderTraverse(tree.root_, [&os](const NodePtr p){
     if (nullptr == p){
     return;
     }
     for ( int i = 0 ; i < 2 ; ++i){
       if(nullptr != p->avl_link_[i]){
         os << "  \"node"<<p->avl_data_ << "\":f"<< i <<" -> \"node" << p->avl_link_[i]->avl_data_ <<"\":f2;\n";
       }
     }
  });
  os << "}\n";
}

// inorder traversing tree
template <class T>
template <class O>
void Adt<T>::InorderTraverse(const typename Adt<T>::NodePtr p, O o) const{

  if (nullptr == p){
    return;
  }
  InorderTraverse(p->avl_link_[0], o);
  o(p);
  InorderTraverse(p->avl_link_[1],o);
}

//probe inserts element into the container, if the container doesn't already contain an element with an equivalent key.
template <class T>
typename Adt<T>::InsertResult  Adt<T>::probe(const T& data){
  NodePtr p, q, n;
  NodePtrStack stack;
  int dir;

  for(q = nullptr, p = root_; p != nullptr; q = p, stack.push_back(q), p = p->avl_link_[dir]){
    auto cmp = data <=> p->avl_data_;
    if (cmp == 0){
      return std::make_pair(Iterator(this, std::move(stack)), false);
    } 
    dir = cmp > 0;
  }

  n = new AvlNode(data);
  ++size_;
  if (q != nullptr){
    q->avl_link_[dir] = n;
  } else {
    root_ = n;
  } 
  return std::make_pair(Iterator(this, std::move(stack)), true);
}

//probe inserts element into the container, if the container doesn't already contain an element with an equivalent key.
template <class T>
typename Adt<T>::InsertResult  Adt<T>::probe_root(const T& data){
  NodePtr p, q, n;
  TraceNodeStack trace_stack;
  trace_stack.reserve(kMaxStack);

  NodePtrStack stack;
  stack.reserve(kMaxStack);

  int dir;
  // place root_ node in 
  trace_stack.emplace_back(root_, 0);

  for(q = nullptr, p = root_; p != nullptr; q = p, stack.push_back(q), p = p->avl_link_[dir]){
    auto cmp = data <=> p->avl_data_;
    if (cmp == 0){
      return std::make_pair(Iterator(this, std::move(stack)), false);
    } 
    dir = cmp > 0;
    trace_stack.emplace_back(p, dir); // save current node and direction in to trace_stack
  }

  n = new AvlNode(data);
  ++size_;

  if (nullptr != root_){
    //attach new node to previous node
    q = trace_stack.back().first;
    dir = trace_stack.back().second;
    q->avl_link[dir] = n;

    // move inserted node to root
    TraceNode tp = trace_stack.back();;
    for ( ; ! trace_stack.empty(); tp = trace_stack.back(), tp.first->avl_link[tp.second] = n ){
      q = tp.first;
      dir = tp.second;
      trace_stack.pop_back();
      if ( dir == 0 ){// perform right rotation
        q->avl_link[0] = n->avl_link[1];
        n->avl_link[1] = q;
      } else {//perform left rotation
        q->avl_link[1] = n->avl_link[0];
        n->avl_link[0] = q;
      }
    }// for
  } // if (nullptr == root_)
  root_ = n;
  return std::make_pair(Iterator(this, root_), true);
}

//Inserts element into the container, if the container doesn't already contain an element with an equivalent key.
template <class T>
typename Adt<T>::InsertResult  Adt<T>::insert(const T& data){
  NodePtr p, q, n;
  NodePtrStack stack;
  stack.reserve(kMaxStack);

  int dir;

  for(q = nullptr, p = root_; p != nullptr; q = p, stack.push_back(q), p = p->avl_link_[dir]){
    auto cmp = data <=> p->avl_data_;
    if (cmp == 0){
      return std::make_pair(Iterator(this, std::move(stack)), false);
    } 
    dir = cmp > 0;
  }

  n = new AvlNode(data);
  ++size_;
  if (q != nullptr){
    q->avl_link_[dir] = n;
  } else {
    root_ = n;
  } 
  return std::make_pair(Iterator(this, std::move(stack)), true);
}


// TODO CONTINUE FROM PAGE 38
// find node equal key , if not found = return end()
template <class T>
typename Adt<T>::Iterator  Adt<T>::find(const T& data){
  NodePtrStack stack;
  stack.reserve(kMaxStack);

  for (NodePtr p = root_; p != nullptr; ){
    auto cmp = data <=> p->avl_data_;
    stack.push_back(p);
    if (cmp < 0){
      p = p->avl_link_[0];
    } else if ( cmp > 0) {
      p = p->avl_link_[1];
    } else {
      return {this, std::move(stack)};
    }
  } 
  return end();
}

}// namespace adt 
