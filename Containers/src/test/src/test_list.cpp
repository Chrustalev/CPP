#include <gtest/gtest.h>

#include "s21_list.hpp"

TEST(List_Constructor, Default) {
  s21::list<int> list_int;
  s21::list<double> list_double;

  EXPECT_EQ(list_int.empty(), 1);
  EXPECT_EQ(list_double.empty(), 1);
}

TEST(List_Constructor, Size) {
  s21::list<int> list_int(3);
  s21::list<double> list_double(5);

  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_double.empty(), 0);
}

TEST(List_Constructor, Initializer_List) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<double> list_double = {2, 1.5, -2};

  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_double.empty(), 0);
}

TEST(List_Constructor, Copy) {
  // s21::list<int> list_int = {1, 3, 5};
  // s21::list<int> list_copy(list_int);

  // EXPECT_EQ(list_copy.empty(), 0);
  // EXPECT_EQ(list_copy.size(), 3);
}

TEST(List_Constructor, Move) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<int> list_move(std::move(list_int));

  EXPECT_EQ(list_int.empty(), 1);
  EXPECT_EQ(list_move.empty(), 0);
  EXPECT_EQ(list_move.size(), 3);
}

TEST(List_Constructor, Operator_Eq) {
  // s21::list<int> list_int = {1, 3, 5};
  // s21::list<int> list_eq;
  // list_eq = std::move(list_int);

  // EXPECT_EQ(list_eq.empty(), 0);
  // EXPECT_EQ(list_eq.size(), 3);
}

// element access

TEST(List_Element_Access, Front) {
  s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.front(), 1);
}

TEST(List_Element_Access, Back) {
  s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.back(), 5);
}

// iterators

TEST(List_Iterators, Begin) {
  s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(*(list_int.begin()), 1);
}

TEST(List_Iterators, cBegin) {
  const s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(*(list_int.cbegin()), 1);
}

TEST(List_Iterators, End) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<int>::iterator it = list_int.end();
  s21::list<int>::iterator it_2 = list_int.begin();
  for (int i = 0; i < 3; ++i) it_2++;

  EXPECT_EQ(it, it_2);
}

TEST(List_Iterators, cEnd) {
  const s21::list<int> list_int = {1, 3, 5};
  s21::list<int>::const_iterator it = list_int.cend();
  s21::list<int>::const_iterator it_2 = list_int.cbegin();
  for (int i = 0; i < 3; ++i) it_2++;

  EXPECT_EQ(it, it_2);
}

// capacity

TEST(List_Capacity, Empty) {
  s21::list<int> list_not_empty = {1, 3, 5};
  s21::list<int> list_empty;

  EXPECT_EQ(list_not_empty.empty(), 0);
  EXPECT_EQ(list_empty.empty(), 1);
}

TEST(List_Capacty, Size) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<int> list_empty;

  EXPECT_EQ(list_int.size(), 3);
  EXPECT_EQ(list_empty.size(), 0);
}

TEST(List_Capacty, Max_Size) {
  s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.max_size() > list_int.size(), 1);
}

// modifiers

TEST(List_Modifiers, Clear) {
  s21::list<int> list_int = {1, 3, 5};

  EXPECT_EQ(list_int.empty(), 0);

  list_int.clear();

  EXPECT_EQ(list_int.empty(), 1);
}

TEST(List_Modifiers, Insert_Front) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.insert(list_int.begin(), 7);

  EXPECT_EQ(list_int.front(), 7);
  EXPECT_EQ(list_int.size(), 4);
}

TEST(List_Modifiers, Insert_Back) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.insert(list_int.end(), 7);

  EXPECT_EQ(list_int.back(), 7);
  EXPECT_EQ(list_int.size(), 4);
}

TEST(List_Modifiers, Insert_Empty_Front) {
  s21::list<int> list_int;
  list_int.insert(list_int.begin(), 1);

  EXPECT_EQ(list_int.front(), 1);
  EXPECT_EQ(list_int.size(), 1);
}

TEST(List_Modifiers, Erase_Front) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.erase(list_int.begin());

  EXPECT_EQ(list_int.front(), 3);
  EXPECT_EQ(list_int.size(), 2);
}

TEST(List_Modifiers, Erase_Empty) {
  s21::list<int> list_int;

  EXPECT_THROW(list_int.erase(list_int.begin()), std::string);
}

TEST(List_Modifiers, Erase_Back) {
  s21::list<int> list_int = {1, 3, 5};
  auto it = list_int.begin();
  it++;
  it++;
  list_int.erase(it);

  EXPECT_EQ(list_int.size(), 2);
  EXPECT_EQ(list_int.back(), 3);
}

TEST(List_Modifiers, Push_Back) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.push_back(7);

  EXPECT_EQ(list_int.back(), 7);
  EXPECT_EQ(list_int.size(), 4);
}

TEST(List_Modifiers, Pop_Back) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.pop_back();

  EXPECT_EQ(list_int.back(), 3);
  EXPECT_EQ(list_int.size(), 2);
}

TEST(List_Modifiers, Pop_Back_Alone) {
  s21::list<int> list_int = {1};
  list_int.pop_back();

  EXPECT_EQ(list_int.empty(), 1);
}

TEST(List_Modifiers, Pop_Back_Empty) {
  s21::list<int> list_int;

  EXPECT_THROW(list_int.pop_back(), std::string);
}

TEST(List_Modifiers, Push_Front) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.push_front(7);

  EXPECT_EQ(list_int.front(), 7);
  EXPECT_EQ(list_int.size(), 4);
}

TEST(List_Modifiers, Push_Front_Empty) {
  s21::list<int> list_int;
  list_int.push_front(7);

  EXPECT_EQ(list_int.front(), 7);
  EXPECT_EQ(list_int.size(), 1);
}

TEST(List_Modifiers, Pop_Front) {
  s21::list<int> list_int = {1, 3, 5};
  list_int.pop_front();

  EXPECT_EQ(list_int.front(), 3);
  EXPECT_EQ(list_int.size(), 2);
}

TEST(List_Modifiers, Pop_Front_Empty) {
  s21::list<int> list_int;

  EXPECT_THROW(list_int.pop_front(), std::string);
}

TEST(List_Modifiers, Pop_Front_Alone) {
  s21::list<int> list_int = {1};
  list_int.pop_front();

  EXPECT_EQ(list_int.empty(), 1);
}

TEST(List_Modifiers, Swap) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<int> list_int_2 = {2, 4};
  list_int.swap(list_int_2);

  EXPECT_EQ(list_int.front(), 2);
  EXPECT_EQ(list_int.back(), 4);
  EXPECT_EQ(list_int.size(), 2);
  EXPECT_EQ(list_int_2.front(), 1);
  EXPECT_EQ(list_int_2.back(), 5);
  EXPECT_EQ(list_int_2.size(), 3);
}

TEST(List_Modifiers, Merge) {
  s21::list<int> list_int = {1, 3, 5};
  s21::list<int> list_int_2 = {0, 4, 6};
  list_int.merge(list_int_2);

  EXPECT_EQ(list_int.front(), 0);
  EXPECT_EQ(list_int.back(), 6);
  EXPECT_EQ(list_int.size(), 6);
  EXPECT_EQ(list_int_2.empty(), 1);
}

TEST(List_Modifiers, Splice) {
  s21::list<int> list_int = {1, 2, 3, 4};
  s21::list<int> list_int_2 = {5, 6, 7};
  auto pos = list_int.begin();
  pos++;
  pos++;
  list_int.splice(pos, list_int_2);

  EXPECT_EQ(list_int.front(), 1);
  EXPECT_EQ(list_int.back(), 4);
  EXPECT_EQ(list_int.size(), 7);
  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_int_2.empty(), 1);
}

TEST(List_Modifiers, Reverse) {
  s21::list<int> list_int = {1, 3, 7, 4};
  list_int.reverse();

  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_int.size(), 4);
  EXPECT_EQ(list_int.front(), 4);
  EXPECT_EQ(list_int.back(), 1);
}

TEST(List_Modifiers, Unique) {
  s21::list<int> list_int = {1, 2, 2, 3, 3, 2, 1, 1, 2};
  list_int.unique();

  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_int.size(), 6);
  EXPECT_EQ(list_int.front(), 1);
  EXPECT_EQ(list_int.back(), 2);
}

TEST(List_Modifiers, Sort) {
  s21::list<int> list_int = {5, 3, 4, 4, 4, 1, 9, 8};
  list_int.sort();

  EXPECT_EQ(list_int.empty(), 0);
  EXPECT_EQ(list_int.size(), 8);
  EXPECT_EQ(list_int.front(), 1);
  EXPECT_EQ(list_int.back(), 9);
}

TEST(List_Insert_Many, Insert_Many) {
  s21::list<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many(list_int.begin(), 3, 4, 5);

  EXPECT_EQ(list_int.size(), 8);
  auto it = list_int.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(List_Insert_Many, Insert_Many_Back) {
  s21::list<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many_back(3, 4, 5);
  auto it = list_int.begin();

  EXPECT_EQ(list_int.size(), 8);
  for (int i = 0; i < 5; ++i) {
    ++it;
  }
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
}

TEST(List_Insert_Many, Insert_Many_Front) {
  s21::list<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many_front(3, 4, 5);
  auto it = list_int.begin();

  EXPECT_EQ(list_int.size(), 8);
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}
