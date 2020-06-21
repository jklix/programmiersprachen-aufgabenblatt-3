#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definitions for the clear method
TEST_CASE("testing clear()","[clear]") {
  List<int> list{};
  list.clear();
  REQUIRE(list.empty());
  list.push_back(3);
  list.clear();
  REQUIRE(list.empty());
  list.push_front(5);
  list.clear();
  REQUIRE(list.empty());
  list.push_back(-1);
  list.push_front(0);
  list.clear();
  REQUIRE(list.empty());
  list.push_front(5);
  list.push_back(20);
  list.push_front(5);
  list.push_back(4);
  list.push_back(-3);
  list.clear();
  REQUIRE(list.empty());
}
//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test cases for the deep-copy method of the list
TEST_CASE("basic testing of copy()", "[copy]") {
  List<int> l{};
  List<int> l1{l};
  REQUIRE(l1.empty());
  l.push_front(4);
  List<int>l2{l};
  REQUIRE(l2.empty() != true);
  l2.pop();
  REQUIRE(l2.empty());
  l.push_back(21);
  l.push_front(10);
  List<int> l3{l};
  REQUIRE(l3.size() == l.size());
}
TEST_CASE("testing copy() with a designated comparison method", "[comp_list]") {
  List<int> l{};
  List<int> l1{l};
  REQUIRE(l.comp_list(l1));
  l.push_front(1);
  REQUIRE(l.comp_list(l1) == false);
  l1.push_back(1);
  REQUIRE(l.comp_list(l1));
  l.push_back(3);
  REQUIRE(l.comp_list(l1) == false);
  l1.push_front(3);
  REQUIRE(l.comp_list(l1) == false);
  l.push_back(1);
  l1.push_front(1);
  REQUIRE(l.comp_list(l1));
}
//test cases for the = operator
TEST_CASE("testing the unifying operator","[unify_operator]") {
  bool print = false;
  List<int> l{};
  List<int> l1{};
  REQUIRE(l1 == l);
  l1.push_back(3);
  l.push_front(4);
  auto ltest(l1);
  REQUIRE(l1 != l);
  REQUIRE(l1 == ltest);
  l1 = l;
  REQUIRE(l1 == l);
  REQUIRE(l1 != ltest);
  l1.pop_front();
  REQUIRE(l1 != l);
  REQUIRE(l.size() == 1);
  REQUIRE(l1.size() == 0);
  l = l1;
  l1.pt_list(print);
  l.pt_list(print);
  REQUIRE(l.size() == 0);
  REQUIRE(l1.size() == 0);
  REQUIRE(l == l1);
  l1.pt_list(print);
  l.pt_list(print);
  l.push_back(29);
  l.push_front(31);
  l.push_back(55);
  l.push_front(34);
  l1.pt_list(print);
  l.pt_list(print);
  REQUIRE(l1 != l);
  l1 = l;
  l1.pt_list(print);
  l.pt_list(print);
  REQUIRE(l1 == l);
  l1.pop_back();
  REQUIRE(l1 != l);
  l.pop_back();
  REQUIRE(l1 == l);
  l1.pt_list(print);
  l.pt_list(print);
}

//test cases for the reverse() methods of the list
TEST_CASE("testing of reverse()","[member_reverse]") {
  bool print = false;
  List<int> l{};
  l.pt_list(print);
  auto l1{l};
  l.reverse();
  REQUIRE(l.comp_list(l1,true));
  l.pt_list(print);
  l.push_front(32);
  REQUIRE(l.comp_list(l1,true) == false);
  l.pt_list(print);
  l.reverse();
  l.pt_list(print);
  l.push_front(21);
  auto l2{l};
  REQUIRE(l.comp_list(l2,true) == false);
  l.pt_list(print);
  l.reverse();
  REQUIRE(l.comp_list(l2,true));
  l.pt_list(print);
  l.push_back(91);
  auto l3{l};
  REQUIRE(l.comp_list(l3,true) == false);
  l.pt_list(print);
  l.reverse();
  REQUIRE(l.comp_list(l3,true));
  l.pt_list(print);
  l.pop_front();
  auto l4{l};
  REQUIRE(l.comp_list(l4,true) == false);
  l.pt_list(print);
  l.reverse();
  REQUIRE(l.comp_list(l4,true));
  l.pt_list(print);
  l.push_back(4);
  l.push_back(7);
  auto l5(l);
  REQUIRE(l.comp_list(l5,true) == false);
  l.pt_list(print);
  l.reverse();
  REQUIRE(l.comp_list(l5,true));
  l.pt_list(print);
  l.pop_back();
  l.pop_front();
  auto l6{l};
  REQUIRE(l.comp_list(l6,true) == false);
  l.pt_list(print);
  l.reverse();
  REQUIRE(l.comp_list(l6,true));
  l.pt_list(print);
}

TEST_CASE("testing of free method reverse()","[free_reverse]") {
  bool print = false;
  List<int> l{};
  l.pt_list(print);
  auto l1 = reverse(l);
  REQUIRE(l.comp_list(l1,true));
  l1.pt_list(print);
  l.push_front(32);
  REQUIRE(l.comp_list(l1,true) == false);
  l.pt_list(print);
  l.push_front(21);
  l.pt_list(print);
  auto l2 = reverse(l);
  REQUIRE(l.comp_list(l1,true) == false);
  l.pt_list(print);
  REQUIRE(l.comp_list(l2,true));
  l.push_back(91);
  auto l3 = reverse(l);
  REQUIRE(l.comp_list(l3,true));
  l3.pt_list(print);
  l.pt_list(print);
  l.pop_front();
  auto l4 = reverse(l);
  REQUIRE(l.comp_list(l4,true));
  l.pt_list(print);
  l4.pt_list(print);
  l.push_back(4);
  l.push_back(7);
  auto l5 = reverse(l);
  REQUIRE(l.comp_list(l5,true));
  l.pt_list(print);
  l5.pt_list(print);
  l.pop_back();
  l.pop_front();
  auto l6 = reverse(l);
  REQUIRE(l.comp_list(l6,true));
  l.pt_list(print);
  REQUIRE(l.comp_list(l6,true));
  l6.pt_list(print);
}

//test cases for == and =! operators
TEST_CASE("testing  == and !=","[equals_operators]") {
  List<int> l{};
  auto l1{l};
  REQUIRE(l == l1);
  REQUIRE((l != l1) == false);
  l.push_front(1);
  REQUIRE(l != l1);
  REQUIRE((l == l1) == false);
  auto l2(l);
  REQUIRE(l == l2);
  REQUIRE((l != l2) == false);
  l1.push_back(1);
  REQUIRE(l == l1);
  REQUIRE((l != l1) == false);
  REQUIRE(l1 == l2);
  REQUIRE((l1 != l2) == false);
  l1.push_back(1);
  l2.push_front(1);
  REQUIRE(l1 == l2);
  l2.push_front(3);
  l1.push_back(3);
  REQUIRE(l2 != l1);
  l2.push_front(43);
  l2.push_front(16);
  l2.push_front(63);
  auto l4(l2);
  REQUIRE(l4 == l2);
  l4.pop_back();
  REQUIRE(l4 != l2);
  REQUIRE(l != l4);
  l2.pop_back();
  REQUIRE(l4 == l2);
  l2.clear();
  REQUIRE(l4 != l2);
  REQUIRE(l != l2);
  l.pop();
  REQUIRE(l == l2);
}

//test cases for the move constructor, till REQ(4==l2.sz) copied from the assignment
TEST_CASE ("testing the move constructor","[constructor]") {
  bool print = true;
  List<int> list ;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List<int> list2 = std::move(list);
  REQUIRE (0 == list.size());
  REQUIRE (list.empty());
  REQUIRE (4 == list2.size());
  list2.push_back(0);
  list2.push_back(-1);
  auto l2tmp(list2);
  list.pt_list(print);
  list = std::move(list2);
  list.pt_list(print);
  list2.pt_list(print);
  REQUIRE (0 == list2.size());
  REQUIRE (list2.empty());
  REQUIRE (4 == list.size());
  REQUIRE (l2tmp != list2);
  REQUIRE (l2tmp == list);
}

//test cases for the initializer list
TEST_CASE("testing the initialiazer list","[init_list]") {
  bool print = false;
  List<int> int_list{9, 5, 38, 100};
  List<int> l1{};
  List<int> l2{1};
  List<int> l3{1, 45, -12, 51, 39, 37, 0};
  List<int> l4{0};
  REQUIRE(int_list.size() == 4);
  REQUIRE(l1.size() == 0);
  REQUIRE(l2.size() == 1);
  REQUIRE(l3.size() == 7);
  REQUIRE(l4.size() == 1);
  int_list.pt_list(print);
  l1.pt_list(print);
  l2.pt_list(print);
  l3.pt_list(print);
  l4.pt_list(print);
}

//test case for +operator
TEST_CASE("testing + for lists","op_plus") {
  bool print = false;
  List<int> l1{1, 2, 3, 4};
  List<int> l2{5, 6, 7, 8};
  List<int> l3{};
  List<int> l4{};
  List<int> l5{0};
  auto test1 = l1 + l2;
  auto test2 = List<int>{1, 2, 3, 4, 5} + List<int>{6, 5, 8, 9};
  auto test3 = l3 + l4;
  auto test4 = l3 + l3 + l3;
  auto test5 = l5 + l5 + l4;
  auto test6 = l1 + l2 + l3 + l4 + l5;
  auto test7 = l1 +l1;
  test1.pt_list(print);
  test2.pt_list(print);
  test3.pt_list(print);
  test4.pt_list(print);
  test5.pt_list(print);
  test6.pt_list(print);
  test7.pt_list(print);
  REQUIRE(test1.size() == 8);
  REQUIRE(test2.size() == 9);
  REQUIRE(test3.size() == 0);
  REQUIRE(test4.size() == 0);
  REQUIRE(test5.size() == 2);
  REQUIRE(test6.size() == 9);
  REQUIRE(test7.size() == 8);
}

//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}




