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


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.12 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.12 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 3)
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 4)

  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.12 - Teil 6)
    // Reuse operator==
    return false;
  } // call it: != it

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

    /* default construction of an empty list with size zero and first_ as well as last_ being nullpointer */
    List(int s = 0, ListNode<T>* p = nullptr): size_(s), first_(p), last_(p) {}

    /*
    Copy constructor creates a new, empty list and a pointer to a node. 
    That pointer gets the value of the node of the original list which is copied into our new list by push_back() since we start at the beginning.
    After that the pointer is set to the next node in the original list
    */
    List(List const& list): size_{0}, first_{nullptr}, last_{nullptr} {
      ListNode<T> *runner = list.first_;
      while(size_ < list.size_) {
        push_back(runner->value);
        runner = runner->next;
      }

    }

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* ... */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)

    /* ... */
    // test and implement:

    bool operator==(List const& rhs) const
    {
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs) const
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    /* calls clear() to destroy the list */
    ~List() {
      clear();
    }

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.11)
      return {};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.11)
      return {};
    }

    /* calls pop_front() as long as the size isn't 0 */ 
    void clear() {
      while (size_ != 0) {
        pop_front();
      }
    }


    /* ... */
    //TODO: member function insert (Aufgabe 3.13)

    /* ... */
    //TODO: member function insert (Aufgabe 3.14)

    /* ... */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
      if (size_ < 2) return;
      ListNode<T>* tmp = new ListNode<T>;
      ListNode<T>* rnr = new ListNode<T>;
      rnr = first_;
      for (int i=0; i < size_; i++) {
        tmp = rnr->next;
        rnr->next = rnr->prev;
        rnr->prev = tmp;
        rnr = rnr->prev;
      }
      first_ = tmp;
      first_ = last_;
      last_ = tmp;
    }
    /*
    small method that gets called if one wants to add a node to an empty list: it creates a new node containing "element", 
    prev and next being defualt-initialiazed as nullptr and first_ and last_ are set to point to the new node and the size is set to 1
    */
    void push(T const& element) {
      ListNode<T>* nw = new ListNode<T>{element};
      first_ = last_ = nw;
      size_ = 1;
    }

    /*
    tests if the list is empty, if it is it calls push()
    if not we make a of the first_ pointer and create a new ListNode containing "element" since we know that the node will be added at the front of the list,
    we can set the prev pointer of the node to nullptr and the next pointer to our previous first_ we then set the pointer of the prev pointer of the former first node
    to the newly added node and set first_ to our new first node. After that we increment the size of the list by one.
    */
    void push_front(T const& element) {
      if(empty()) push(element);
      else {
        ListNode<T>* fst = first_; 
        ListNode<T>* nw = new ListNode<T>{element, nullptr, fst};
        fst->prev = first_ = nw;
        size_++;
      }
    }

    /* 
    we do the exact same thing as in push_front(), with the exception that "first" is swapped with "last", "front" with "back" and "prev" and next" have switched places.
    */
    void push_back(T const& element) {
      if(empty()) push(element);
      else {
        ListNode<T>* lst = last_;
        ListNode<T>* nw = new ListNode<T>{element, lst, nullptr};
        lst->next = last_ = nw;
        size_++;
      }
    }

    /*
    small method that gets called if pop_front() or pop_back() is called and list size is 1
    it deletes the single list object, sets the pointers from first_ and last_ to nullptr and sets the size to zero
    */
    void pop() {
      delete(first_);
      first_ = last_ = nullptr;
      size_ = 0;
    }

    /* 
    tests if the list is empty, if so it throws an exception
    if the size of the list is one it calls pop()
    in all other cases it makes a copy of the pointers first_ and first_->next, the first two nodes in the list,
    sets first_ to the second node and deletes the former first node, then sets the prev-pointer of the new first node to nullptr and increments size_ by one
    */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      if (size_ == 1) pop();
      else {
        ListNode<T>* del = first_;
        ListNode<T>* prv = first_->next;
        first_ = prv;
        prv -> prev = nullptr;
        delete(del); 
        size_--;
      }
    }

    /*
    does basically as pop_front(), with the exception that we now use the last and second last node of our list
    so we make the copys, set last_ to the second lst node, delete the former last node and set the next pointer of the new last node to nullptr and increments size_ by one
    */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      if (size_ == 1) pop();
      else {
        ListNode<T>* del = last_;
        ListNode<T>* prv = last_->prev;
        last_ = prv;
        prv -> next = nullptr;
        delete(del);
        size_--;
        
      }
    }

    /* returns the value of the first node */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      return first_->value;
    }

    /* returns the value of the last node*/
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      return last_->value;
    }

    /* checks if the size of the list is zero and acts and acts accordingly */
    bool empty() const {
      return (size_ == 0) ? true : false;
    };


    /* returns the size of the list */
    std::size_t size() const{     
      return size_;
    };

    /* 
    related to 3.5 copy()
    compares two lists and checks if they share the same element-values at the same postition 
    if the element values of the lists are identical, it returns true.
    */
    bool comp_list(List const& l) {
      if (size_ != l.size_) return false;
      //the condition below could be commented out since the method would handle it correctly anyway, however it is more efficient to do it like this
      if (size_ == 0) return true;
      ListNode<T>* rnr_l1 = new ListNode<T>;
      ListNode<T>* rnr_l2 = new ListNode<T>;
      rnr_l1 = first_;
      rnr_l2 = l.first_;
      while ((rnr_l1 != nullptr) && (rnr_l2 != nullptr)){
        if (rnr_l1->value != rnr_l2->value) return false;
        rnr_l1 = rnr_l1->next;
        rnr_l2 = rnr_l2->next;
      }
      if ((rnr_l1 == nullptr) && (rnr_l2 == nullptr)) return true;
      return false;
    };

    /*
    related to 3.7
    small helper function that prints the values of the elements of the list front to back
    */
    void pt_list() {
      ListNode<T>* rnr = new ListNode<T>;
      rnr = first_;
      std::cout << "The selected list has the size " << size_ << " and contains elements with the following values: ";
      while (rnr != nullptr) {
        std::cout << "[ " << rnr->value << " ] ";
        rnr = rnr->next;
      }
      std::cout << "\n";
    }


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* 
reverse() first creates a new List, deep-copying "l" , then it calls the member function reverse() on the newly created list and returns it.
 */
template<typename T>
List<T> reverse(List<T>& l) {
  List<T> revl(l);
  return (revl.reverse());
}
/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
