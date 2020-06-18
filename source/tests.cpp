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
TEST_CASE("testing copy()", "[copy]") {
  List<int> l{};
  List<int> l1(l);
  REQUIRE(l1.empty());
  l.push_front(4);
  List<int>l2(l);
  REQUIRE(l2.empty() != true);
  l2.pop();
  REQUIRE(l2.empty());
  //I can't compare values since first_ and last_ are private, so only the size is comparable
  l.push_back(21);
  l.push_front(10);
  List<int> l3(l);
  REQUIRE(l3.size() == l.size());
}
TEST_CASE("testing copy() with a designated comparison method", "[comp_list]") {
  List<int> l{};
  List<int> l1(l);
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




