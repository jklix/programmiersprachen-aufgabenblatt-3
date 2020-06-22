#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};

template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  //3.12

  /* Operator*() returns the value which the node of the LiIt points to */
  T& operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else {
      return node->value;
    }
  }

  /* Operator->() returns a pointer to the value which the node of the LiIt is pointing to */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else {
      return &node->value;
    }
  }


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    node = node->next;
    return *this;
  }

  /* 
  POSTINCREMENT (signature distinguishes the iterators), advances one element forward
  when the next node is a nullptr it has no prev pointer, so we initialiaze a ListIterator.
  Since it wasn't initialiazed with a value it will just contain a nullptr.
  we then iterate forward ba swapping our current ListIterator with the newly created one.
  if the next node is not a nullptr we can just set our node to the next node and return the node we started with.
  */
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    if(node->next == nullptr) {
      ListIterator<T> tmp{};
      std::swap(*this, tmp);
      return tmp;
    }
    else {
      node = node->next;
      return{node->prev};
    }
  }


  /* Checks if the pointers of the nodes of the two ListIterators are the same. */
  bool operator==(ListIterator<T> const& x) const {
    return(node == x.node) ? true : false;
  }

  /* Compares two ListIterators by using the previously implemented == operator. */
  bool operator!=(ListIterator<T> const& x) const {
    return(*this == x) ? false : true;
  }

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    /* 3.2 default construction of an empty list with size_ = 0 and first_ as well as last_ being nullpointer */
    List(int s = 0, ListNode<T>* p = nullptr): size_(s), first_(p), last_(p) {}

    /*
    3.5
    Copy constructor creates a new, empty list and a pointer to a node. 
    That pointer gets the value of the node of the original list which is copied into our new list by push_back().
    After that the pointer is set to the next node in the original list, this goes till the list sizes are equal (and all elements copied).
    */
    List(List const& list): size_{0}, first_{nullptr}, last_{nullptr} {
      auto rnr = list.first_;
      while(size_ < list.size_) {
        push_back(rnr->value);
        rnr = rnr->next;
      }

    }
    /* 
    3.9 move operator:
    We copy the member-vars directly into a new list, then set the values of the list we copied it from to 0 / nullptr to get a empty list 
    */
    List(List&& rhs) : size_{rhs.size_}, first_{rhs.first_}, last_{rhs.last_} {
      rhs.size_ = 0;
      rhs.first_ = rhs.last_ = nullptr;
    }

    /* Implementation of the initializer list, based on the requirements in 3.10 */
    List(std::initializer_list<T> ini_list) : size_{0}, first_{nullptr}, last_{nullptr} {
      for (auto& i : ini_list) {
        push_back(i);
      }
    }

    /* 3.6 Implementation of the unifying copy and swap -assignment operator, based on the provided slides. */
    List& operator=(List rhs) {
      swap(rhs);
      return *this;
    }

    /* Related to 3.6: Small helper function to swap the fist and last pointers of two lists */
    void swap(List& l) {
      std::swap(first_, l.first_);
      std::swap(last_, l.last_);
      std::swap(size_, l.size_);
    }

    /* 
    3.8
    Checks if two lists are equal (in element count and -position) or not using comp_list()
    and returns a bool based on that. 
    */
    bool operator==(List const& rhs) const
    { 
      return comp_list(rhs);
    }

    bool operator!=(List const& rhs) const
    {
      return (*this == rhs ? false : true);
      //return (comp_list(rhs) ? false : true);
    }

    /* 3.4 Calls clear() to destroy the list. */
    ~List() {
      clear();
    }

    /* 3.11 List Iterator, pointing to the first element in the list. */
    ListIterator<T> begin() {
      return {first_};
    }

    /* 3.11 List Iterator pointing to the element behind the last element of the list. */
    ListIterator<T> end() {
      return {nullptr};
    }

    /* 3.4 Calls pop_front() as long as the size isn't 0. */ 
    void clear() {
      while (size_ != 0) {
        pop_front();
      }
    }


    /*
    3.13
    for Insert we can partly utilize push_*;
    If the node of the ListIterator in a nullpointer, we can use push front, since it can handle both empty and non-empty lists
    When inserting between two elements we first get a ListIterator from the next element.
    This way we can initialize our new element directly with the right pointers. After that we just need to update the pointer
    of the bf (before) and bh (behind) nodes so that they point to the newly inserted node and increase the size by one.
    Lastly we set bf to point to our new elementby using bf.next()
    */
    ListIterator<T> insert(T const& val, ListIterator<T> bf) {
      if (bf.node == nullptr) {
        push_front(val);
        return{first_};
      }
      if ((bf.node != nullptr) && (bf.node->next != nullptr)) {
        ListIterator<T> bh{bf.next()};
        ListNode<T>* n = new ListNode<T>{val, bf.node, bh.node};
        bf.node->next = n;
        bh.node->prev = n;
        size_++;
        bf = bf.next();
        return bf;
      }
      else {
        push_back(val);
        return{last_};
      }
    }

    /*
    3.14
    Very similar to the insert() method, we need to check different edge-cases and act accordingly:
    If the node of the ListIterator is a nullpointer we return a nullptr, since that isn't pointing to any element.
    If we get a pointer to the first element we can utilize pop_front() and return the new first_ pointer.
    The same applies if the node points to the last element in the list (although we then return a nullpointer for the next element since there is none).
    If an element between two other elements should be deleted we first make two new ListIterators,
    one that points to the element before our element and one that points to the element behind it.
    We then delete the element in the middle and set the pointers from bf and bh to their new next / prev element.
    After that we decrease the size by one and return the ListIterator bh.
    */
    ListIterator<T> erase(ListIterator<T> del) {
      if (del.node == first_) {
        pop_front();
        return{first_};
      }
      if ((del.node != nullptr) && (del.node->next != nullptr)) {
        ListIterator<T> bf{del.node->prev};
        ListIterator<T> bh{del.node->next};
        delete(del.node);
        bh.node->prev = bf.node;
        bf.node->next = bh.node;
        size_--;
        return bh;
      }
      if (del.node == last_) {
        pop_back();
      }
      return{nullptr};
    }

    /*
    3.7
    Reversing the order of element-values in the list by flipping the pointers of the nodes.
    If the list size is smaller than 2 we don't have to do anything.
    In every other case we have a runner node, starting at "first_" and working its way trough the list, flipping "prev" and "next" pointer using tmp as storage.
    When it has finished it then flips the first and last pointers of the list
    */
    void reverse() {
      if (size_ < 2) return;
      ListNode<T>* tmp = new ListNode<T>;
      auto rnr = first_;
      while (rnr != nullptr) {
        tmp = rnr->next;
        rnr->next = rnr->prev;
        rnr->prev = tmp;
        rnr = rnr->prev;
      }
      if (first_->next == nullptr) std::swap(first_, last_);

    }

    /*
    3.3
    Small method that gets called if one wants to add a node to an empty list: It creates a new node containing "element", 
    prev and next being defualt-initialiazed as nullptr and first_ and last_ are set to point to the new node and the size is set to 1.
    */
    void push(T const& element) {
      ListNode<T>* nw = new ListNode<T>{element};
      first_ = last_ = nw;
      size_ = 1;
    }

    /*
    3.3
    Tests if the list is empty, if it is it calls push()
    If not we make a copy of the first_ pointer and create a new ListNode containing "element". Since we know that the node will be added at the front of the list,
    we can set the prev pointer of the node to nullptr and the next pointer to our previous first_. We then set the pointer of the prev pointer of the former first node
    to the newly added node and set first_ to our new first node. After that we increment the size of the list by one.
    */
    void push_front(T const& element) {
      if(empty()) push(element);
      else {
        auto fst = first_; 
        ListNode<T>* nw = new ListNode<T>{element, nullptr, fst};
        fst->prev = first_ = nw;
        size_++;
      }
    }

    /*
    3.3 
    We do the exact same thing as in push_front(), with the exception that "first" is swapped with "last", "front" with "back" and "prev" and next" have switched places.
    */
    void push_back(T const& element) {
      if(empty()) push(element);
      else {
        auto lst = last_;
        ListNode<T>* nw = new ListNode<T>{element, lst, nullptr};
        lst->next = last_ = nw;
        size_++;
      }
    }

    /*
    3.3
    small method that gets called if pop_front() or pop_back() are called and list size is 1.
    It deletes the single list element, sets the pointers first_ and last_ to nullptr and the size to zero
    */
    void pop() {
      delete(first_);
      first_ = last_ = nullptr;
      size_ = 0;
    }

    /*
    3.3
    Tests if the list is empty, if so it throws an exception.
    If the size of the list is one it calls pop().
    In all other cases it makes a copy of the pointers first_ and first_->next, the first two nodes in the list,
    sets first_ to the second node and deletes the former first node, then sets the prev-pointer of the new first node to nullptr and increments size_ by one.
    */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      if (size_ == 1) pop();
      else {
        auto del = first_;
        auto prv = first_->next;
        first_ = prv;
        prv -> prev = nullptr;
        delete(del); 
        size_--;
      }
    }

    /*
    3.3
    Does basically the same as pop_front(), with the exception that we now use the last and second last node of our list.
    We make the copys, set last_ to the second lst node, delete the former last node and set the next pointer of the new last node to nullptr and increments size_ by one
    */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      if (size_ == 1) pop();
      else {
        auto del = last_;
        auto prv = last_->prev;
        last_ = prv;
        prv -> next = nullptr;
        delete(del);
        size_--;
        
      }
    }

    /* returns the value of the first node */
    T& front() const {
      if(empty()) {
        throw "List is empty";
      }
      return first_->value;
    }

    /* returns the value of the last node*/
    T& back() const {
      if(empty()) {
        throw "List is empty";
      }
      return last_->value;
    }

    /* 3.2 checks if the size of the list is zero and acts and acts accordingly */
    bool empty() const {
      return (size_ == 0) ? true : false;
    };


    /* 3.2 returns the size of the list */
    std::size_t size() const{     
      return size_;
    };

    /* 
    related to 3.5 copy()
    compares two lists and checks if they share the same element-values at the same postition 
    if the element values of the lists are identical, it returns true.
    related to 3.7 reverse()
    if the boolean is set to true it will test if the two lists are equal when one is reversed
    */
    bool comp_list(List const& l, bool reverse = false) const {
      if (size_ != l.size_) return false;
      //the condition below could be commented out since the method would handle it correctly anyway, however it is more efficient to do it like this
      if (size_ == 0) return true;
      auto rnr_l1 = first_;
      auto rnr_l2 = (reverse ? l.last_ : l.first_);
      while ((rnr_l1 != nullptr) && (rnr_l2 != nullptr)){
          if (rnr_l1->value != rnr_l2->value) return false;
          rnr_l1 = rnr_l1->next;
          rnr_l2 = (reverse ? rnr_l2->prev : rnr_l2->next);
      }
      return true;
    };

    /*
    -.--
    Just a small helper for debugging: goes through the list, front to back, printing pointer to elements as well as their value and the list size.
    For convenience while testing it has a bool to toggle between output and no output.
    */
    void pt_list(bool b) {
      if (b) {
        auto rnr = first_;
        std::cout << "The selected list has the size " << size_ << " and contains elements with the following values: "<< first_ << "->\n";
        while (rnr != nullptr) {
          std::cout << "<- " << rnr->prev << "[ " << rnr->value << " ] " << rnr->next << " -> ";
          rnr = rnr->next;
        }
        std::cout << "\n<-" << last_ <<"\n";
      }
    }


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* 
3.7
reverse() first creates a new List, deep-copying "l", then calls the member function reverse() on the newly created list and returns it.
 */
template<typename T>
List<T> reverse(List<T> const& l) {
  auto revl(l);
  revl.reverse();
  return revl;
}
/* 
3.10
Creates copies of the operators because we want to be able to use ListIterators.
Then we add to tmp1 all the element values of tmp2 using a range-based for loop before returning tmp1.
*/
template<typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs) {
  auto tmp1(lhs);
  auto tmp2(rhs);
  for (auto const& i : tmp2) tmp1.push_back(i);
  return tmp1;
}

/*
3.15
Small function to test if a vector and list contain the same elements at the same position.
First we check if their size is the same and, if that is the case, if it also is zero.
If the size is not zero we copy-construct a temporary list since we can't work with ListIterators otherwise.
We then initialize vecit with zero and use a range based for loop to iterate over the elements in the copied list.
For each element we check if it has the same value as the element found in the vector, then we increase vecit by one.
*/
template <typename T>
bool has_same_content (List<T> const& list, std::vector<T> const& vec) {
  if (list.size() != vec.size()) return false;
  if (list.size() == 0) return true;
  List<int> tmp(list);
  int vecit = 0;
  for (auto const& i : tmp) {
    if (i != vec[vecit]) return false;
    vecit++;
  }
  return true;
}

#endif // # define BUW_LIST_HPP
