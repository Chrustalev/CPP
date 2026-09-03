#include <gtest/gtest.h>

#include <iterator>
#include <set>

#include "s21_set.hpp"

//---------------- FIRST ATTEMPT ----------------//

TEST(set, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, InsertSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(set, EraseSet) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};

  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();

  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SwapSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, MergeSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, FindSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, ContainsSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

//---------------- SECOND ATTEMPT ----------------//

TEST(set_constructor, case1) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_EQ(s21_set_int.size(), 0U);
  EXPECT_EQ(s21_set_double.size(), 0U);
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set_constructor, case2) {
  s21::set<int> s21_set_int{1, 2, 3, 4, 5};
  s21::set<double> s21_set_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> s21_set_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_set_int.size(), 5U);
  EXPECT_EQ(s21_set_double.size(), 3U);
  EXPECT_EQ(s21_set_string.size(), 4U);
}

TEST(set_constructor, case3) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  EXPECT_EQ(s21_set_ref_int.size(), s21_set_res_int.size());
  EXPECT_EQ(s21_set_ref_double.size(), s21_set_res_double.size());
  EXPECT_EQ(s21_set_ref_string.size(), s21_set_res_string.size());
}

TEST(set_constructor, case4) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case5) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double;
  s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case7) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  auto it_res_int = s21_set_res_int.begin();
  for (auto it_ref_int = s21_set_ref_int.begin();
       it_ref_int != s21_set_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = s21_set_res_double.begin();
  for (auto it_ref_double = s21_set_ref_double.begin();
       it_ref_double != s21_set_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = s21_set_res_string.begin();
  for (auto it_ref_string = s21_set_ref_string.begin();
       it_ref_string != s21_set_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(set_insert, case1) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case2) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case3) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case4) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert, case5) {
  s21::set<double> s21_set = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_insert, case6) {
  s21::set<std::string> s21_set = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_begin, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*s21_set.begin(), 2);
}

TEST(set_begin, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*s21_set.begin(), 2.77);
}

TEST(set_begin, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hi-hi", "hola",
                                   "hello, there"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_begin, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*s21_set.begin(), 1.4);
}

TEST(set_begin, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_end, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*(--s21_set.end()), 23);
}

TEST(set_end, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 11.400000001, 3.9};

  EXPECT_EQ(*(--s21_set.end()), 11.400000001);
}

TEST(set_end, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
}

TEST(set_end, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*(--s21_set.end()), 1.4);
}

TEST(set_end, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*(--s21_set.end()), "hello");
}

TEST(set_balance, case1) {
  s21::set<int> s21_set = {1, 15, 5};

  EXPECT_EQ(*(--s21_set.end()), 15);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*(--s21_set.end()), 11.4);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case4) {
  s21::set<int> s21_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*(--s21_set.end()), 1543);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case5) {
  s21::set<int> s21_set = {30, 5, 43, 1, 20, 40, 60, 35, 32};

  EXPECT_EQ(*(--s21_set.end()), 60);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(s21_set.size(), 9U);
}

TEST(set_erase, case1) {
  s21::set<int> s21_set = {10, 5, 15, 4, 18, 13, 16};

  auto it = s21_set.begin();
  it = std::next(it, 5);

  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 4);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 6U);

  it = s21_set.begin();
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 5U);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.end();
  s21_set.erase(--it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 15);
  EXPECT_EQ(s21_set.size(), 3U);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case2) {
  s21::set<int> s21_set = {30, 1543};
  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case6) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 6.84, 1.44};

  auto it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();

  it = std::next(it, 3);
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case7) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case8) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case9) {
  s21::set<double> s21_set = {22.2,  44.48, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = s21_set.end();
  it = std::next(it, -4);

  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 32.45);
  EXPECT_EQ(s21_set.size(), 7U);
}

TEST(set_erase, case10) {
  s21::set<double> s21_set = {22.2};

  auto it = s21_set.end();
  --it;
  s21_set.erase(it);
  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_empty, case1) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.empty(), 0);
}

TEST(set_empty, case2) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.empty(), 1);
}

TEST(set_MaxSize, case1) {
  s21::set<double> s21_set;
  std::set<double> std_set;

  s21_set.max_size();
}

TEST(set_MaxSize, case2) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};
  std::set<double> std_set = {22.2, 44.48, 12.4457, 1.44};

  s21_set.max_size();
}

TEST(set_swap, case1) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_swap, case4) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_contains, case1) {
  s21::set<double> s21_set = {22.2, 44.48};

  EXPECT_EQ(s21_set.contains(22.2), true);
  EXPECT_EQ(s21_set.contains(44.48), true);
}

TEST(set_contains, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_ref.contains(22.2), false);
  EXPECT_EQ(s21_set_ref.contains(44.48), false);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(s21_set_res.contains(22.2), true);
  EXPECT_EQ(s21_set_res.contains(44.48), true);
}

TEST(set_contains, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(s21_set_ref.contains(12.4457), true);
  EXPECT_EQ(s21_set_ref.contains(1.44), true);
  EXPECT_EQ(s21_set_ref.contains(22.2), true);

  EXPECT_EQ(s21_set_res.size(), 0U);
  EXPECT_EQ(s21_set_res.contains(12.4457), false);
  EXPECT_EQ(s21_set_res.contains(1.44), false);
  EXPECT_EQ(s21_set_res.contains(22.2), false);
}

TEST(set_contains, case4) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.contains(12.4457), false);
}

TEST(set_find, case2) {
  s21::set<double> s21_set = {12.4457, 1.44, 22.2};

  auto it = s21_set.begin();
  ++it;
  EXPECT_EQ(*s21_set.find(12.4457), *it);

  it--;
  EXPECT_EQ(*s21_set.find(1.44), *it);

  it = std::next(it, 2);
  EXPECT_EQ(*s21_set.find(22.2), *it);
}

// // TEST(set_emplace, case1) {
// //   s21::set<int> s21_set;

// //   std::vector<std::pair<s21::set<int>::iterator, bool>> emplace1 =
// //       s21_set.emplace(9, 9, 9, 23, 98);

// //   EXPECT_EQ(*emplace1[0].first, 23);
// //   EXPECT_EQ(emplace1[0].second, true);
// //   EXPECT_EQ(s21_set.size(), 3U);
// // }

// // TEST(set_emplace, case2) {
// //   s21::set<double> s21_set;

// //   std::vector<std::pair<s21::set<double>::iterator, bool>> emplace1 =
// //       s21_set.emplace(1.4, 2.77, 3.9, 2.77, 3.9);

// //   EXPECT_EQ(*emplace1[0].first, 2.77);
// //   EXPECT_EQ(emplace1[0].second, true);
// //   EXPECT_EQ(s21_set.size(), 3U);
// // }

// // TEST(set_emplace, case3) {
// //   s21::set<std::string> s21_set;

// //   std::vector<std::pair<s21::set<std::string>::iterator, bool>> emplace1 =
// //       s21_set.emplace("hello", "hi", "hi", "hola", "hello");

// //   EXPECT_EQ(*emplace1[0].first, "hi");
// //   EXPECT_EQ(emplace1[0].second, true);
// //   EXPECT_EQ(s21_set.size(), 3U);
// // }

// // TEST(set_emplace, case4) {
// //   s21::set<int> s21_set;

// //   std::vector<std::pair<s21::set<int>::iterator, bool>> emplace1 =
// //       s21_set.emplace(9);

// //   EXPECT_EQ(*emplace1[0].first, 9);
// //   EXPECT_EQ(emplace1[0].second, true);
// //   EXPECT_EQ(s21_set.size(), 1U);
// // }

// // TEST(set_emplace, case5) {
// //   s21::set<double> s21_set = {1.4};

// //   std::vector<std::pair<s21::set<double>::iterator, bool>> emplace1 =
// //       s21_set.emplace(1.4);

// //   EXPECT_EQ(emplace1[0].second, false);
// //   EXPECT_EQ(s21_set.size(), 1U);
// // }

// // TEST(set_emplace, case6) {
// //   s21::set<std::string> s21_set = {"hello"};

// //   std::vector<std::pair<s21::set<std::string>::iterator, bool>> emplace1 =
// //       s21_set.emplace("hi");

// //   EXPECT_EQ(*emplace1[0].first, "hi");
// //   EXPECT_EQ(emplace1[0].second, true);
// //   EXPECT_EQ(s21_set.size(), 2U);
// // }

// //---------------- THIRD ATTEMPT ----------------//

TEST(S21setTest, DefaultConstructor) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  ASSERT_EQ(0U, set.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, InitializerListConstructor) {
  s21::set<int> set({1, 2, 3});
  ASSERT_FALSE(set.empty());
  ASSERT_EQ(3U, set.size());
}

TEST(S21setTest, CopyConstructor) {
  s21::set<int> set({1, 2, 3});
  const s21::set<int>& copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21setTest, MoveConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> move(std::move(set));
  ASSERT_TRUE(set.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, AssignmentOperator1) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = set1;
  ASSERT_FALSE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(set1.size(), set2.size());
}

TEST(S21setTest, AssignmentOperator2) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = std::move(set1);
  ASSERT_TRUE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(3U, set2.size());
}

TEST(S21setTest, IteratorBegin) {
  s21::set<int> set({1, 2, 3});
  s21::set<int>::iterator it;
  it = set.begin();
  s21::set<int>::iterator it_find;
  it_find = set.find(1);
  ASSERT_TRUE(it == it_find);
  ASSERT_EQ(it_find, it);
}

TEST(S21setTest, CapacityEmpty) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21setTest, CapacitySize) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  EXPECT_EQ(set.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

// TEST(S21setTest, CapacityMaxSize) {
// s21::set<int> set({1, 2, 3});
// EXPECT_EQ(set.max_size(), std::numeric_limits<size_t>::max());
// }

TEST(S21setTest, ModifierClear) {
  s21::set<int> set({1, 2, 3});
  ASSERT_FALSE(set.empty());
  set.clear();
  ASSERT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, ModifierInsert1) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21setTest, ModifierInsert2) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21setTest, ModifierErase) {
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(set.size(), 3U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.contains(2));
}

TEST(S21setTest, ModifierSwap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_EQ(set2.size(), 3U);
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
  ASSERT_TRUE(set1.contains(6));
  ASSERT_TRUE(set2.contains(1));
  ASSERT_TRUE(set2.contains(2));
  ASSERT_TRUE(set2.contains(3));
}

TEST(S21setTest, ModifierMerge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 5U);
  EXPECT_EQ(set2.size(), 1U);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
}

// ==================== SET TESTS ====================
TEST(SetInsertManyTest, InsertMany_Basic) {
  s21::set<int> s;

  auto results = s.insert_many(10, 20, 30, 10, 40);

  EXPECT_EQ(results.size(), 5);
  EXPECT_TRUE(results[0].second);   // 10 - успешно
  EXPECT_TRUE(results[1].second);   // 20 - успешно
  EXPECT_TRUE(results[2].second);   // 30 - успешно
  EXPECT_FALSE(results[3].second);  // 10 - уже есть
  EXPECT_TRUE(results[4].second);   // 40 - успешно

  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(10));
  EXPECT_TRUE(s.contains(20));
  EXPECT_TRUE(s.contains(30));
  EXPECT_TRUE(s.contains(40));
  EXPECT_FALSE(s.contains(50));
}

TEST(SetInsertManyTest, InsertMany_Strings) {
  s21::set<std::string> s;

  auto results = s.insert_many("apple", "banana", "cherry", "apple", "date");

  EXPECT_EQ(results.size(), 5);
  EXPECT_TRUE(results[0].second);   // "apple" - успешно
  EXPECT_TRUE(results[1].second);   // "banana" - успешно
  EXPECT_TRUE(results[2].second);   // "cherry" - успешно
  EXPECT_FALSE(results[3].second);  // "apple" - уже есть
  EXPECT_TRUE(results[4].second);   // "date" - успешно

  EXPECT_EQ(s.size(), 4);
}

TEST(SetInsertManyTest, InsertMany_EmptyArgs) {
  s21::set<int> s{1, 2, 3};

  auto results = s.insert_many();

  EXPECT_EQ(results.size(), 0);
  EXPECT_EQ(s.size(), 3);
}

TEST(SetInsertManyTest, InsertMany_MixedTypesWithConversion) {
  s21::set<double> s;

  auto results = s.insert_many(1, 2.5, 3, 4.7);

  EXPECT_EQ(results.size(), 4);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_TRUE(results[3].second);

  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(1.0));
  EXPECT_TRUE(s.contains(2.5));
}

TEST(SetInsertManyEdgeTest, InsertMany_ReserveCoverage) {
  s21::set<int> s;

  auto results = s.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

  EXPECT_EQ(results.size(), 10);
  EXPECT_EQ(s.size(), 10);

  for (int i = 1; i <= 10; ++i) {
    EXPECT_TRUE(s.contains(i));
  }
}

TEST(SetInsertManyEdgeTest, InsertMany_SingleElement) {
  s21::set<int> s{1, 2, 3};

  auto results = s.insert_many(4);

  EXPECT_EQ(results.size(), 1);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(s.contains(4));
}

TEST(SetInsertManyEdgeTest, InsertMany_AllDuplicates) {
  s21::set<int> s{1, 2, 3};

  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(results.size(), 3);
  EXPECT_FALSE(results[0].second);
  EXPECT_FALSE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_EQ(s.size(), 3);
}

// ==================== CROSS-CONTAINER TESTS ====================
// TEST(InsertManyCrossTest, ReturnTypeCheck) {
//   // Проверяем, что возвращаемые типы правильные
//   s21::set<int> s;
//   s21::multiset<int> ms;
//   s21::map<int, int> m;

//   auto s_result = s.insert_many(1, 2, 3);
//   auto ms_result = ms.insert_many(1, 2, 3);
//   auto m_result = m.insert_many(std::make_pair(1, 10), std::make_pair(2,
//   20));

//   // Проверяем типы возвращаемых значений
//   EXPECT_EQ(typeid(s_result),
//             typeid(s21::vector<std::pair<s21::set<int>::iterator, bool>>));
//   EXPECT_EQ(typeid(ms_result),
//             typeid(s21::vector<s21::multiset<int>::iterator>));
//   EXPECT_EQ(typeid(m_result),
//             typeid(s21::vector<std::pair<s21::map<int, int>::iterator,
//             bool>>));

//   // Проверяем размеры
//   EXPECT_EQ(s_result.size(), 3);
//   EXPECT_EQ(ms_result.size(), 3);
//   EXPECT_EQ(m_result.size(), 2);
// }

// TEST(InsertManyCrossTest, IteratorValidity) {
//   s21::set<int> s{1, 2, 3};
//   s21::multiset<int> ms{1, 2, 3};
//   s21::map<int, std::string> m{{1, "a"}, {2, "b"}};

//   // Вставляем новые элементы
//   auto s_res = s.insert_many(4, 5);
//   auto ms_res = ms.insert_many(4, 4, 5);
//   auto m_res = m.insert_many(std::make_pair(3, "c"), std::make_pair(4, "d"));

//   // Проверяем, что возвращенные итераторы валидны
//   for (const auto& p : s_res) {
//     EXPECT_NE(p.first, s.end());
//     if (p.second) {
//       EXPECT_EQ(*p.first, 4);  // Первый успешно вставленный
//       break;
//     }
//   }

//   for (const auto& it : ms_res) {
//     EXPECT_NE(it, ms.end());
//   }

//   for (const auto& p : m_res) {
//     EXPECT_NE(p.first, m.end());
//   }
// }