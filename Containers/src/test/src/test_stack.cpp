#include <gtest/gtest.h>

#include "s21_stack.hpp"

TEST(Stack_Constructor, Default) {
  s21::stack<int> int_s;
  s21::stack<double> double_s;
  EXPECT_EQ(int_s.empty(), 1);
  EXPECT_EQ(double_s.empty(), 1);
}

TEST(Stack_Constructor, Initializer_List) {
  s21::stack<int> int_s = {1, 2, 3};
  EXPECT_EQ(int_s.size(), 3);
  EXPECT_EQ(int_s.empty(), 0);
}

TEST(Stack_Constructor, Copy) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2(int_s1);
  EXPECT_EQ(int_s2.empty(), 0);
}

TEST(Stack_Constructor, Move) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2(std::move(int_s1));
  EXPECT_EQ(int_s2.empty(), 0);
  EXPECT_EQ(int_s1.empty(), 1);
}

TEST(Stack_Constructor, Operator_eq) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2;
  int_s2 = std::move(int_s1);
  EXPECT_EQ(int_s2.size(), 3);
  EXPECT_EQ(int_s1.size(), 0);
}

TEST(Stack_Element_Access, Top) {
  s21::stack<int> int_s = {1, 2, 3};
  EXPECT_EQ(int_s.top(), 3);
}

TEST(Stack_Element_Access, Top_Empty) {
  s21::stack<int> int_s;
  EXPECT_THROW(int_s.top(), std::out_of_range);
}

TEST(Stack_Capacity, Empty) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2;
  EXPECT_EQ(int_s1.empty(), 0);
  EXPECT_EQ(int_s2.empty(), 1);
}

TEST(Stack_Capacity, Size) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2;
  EXPECT_EQ(int_s1.size(), 3);
  EXPECT_EQ(int_s2.size(), 0);
}

TEST(Stack_Modifiers, Push) {
  s21::stack<int> int_s = {1, 2, 3};
  int_s.push(7);
  EXPECT_EQ(int_s.size(), 4);
  EXPECT_EQ(int_s.top(), 7);
}

TEST(Stack_Modifiers, Push_Empty) {
  s21::stack<int> int_s;
  int_s.push(7);
  EXPECT_EQ(int_s.empty(), 0);
  EXPECT_EQ(int_s.size(), 1);
}

TEST(Stack_Modifiers, Pop) {
  s21::stack<int> int_s = {1, 2, 3};
  int_s.pop();
  EXPECT_EQ(int_s.top(), 2);
}

TEST(Stack_Modifiers, Pop_Empty) {
  s21::stack<int> int_s;
  EXPECT_THROW(int_s.pop(), std::out_of_range);
}

TEST(Stack_Modifiers, Swap) {
  s21::stack<int> int_s1 = {1, 2, 3};
  s21::stack<int> int_s2;
  EXPECT_EQ(int_s1.empty(), 0);
  EXPECT_EQ(int_s2.empty(), 1);
  int_s1.swap(int_s2);
  EXPECT_EQ(int_s1.empty(), 1);
  EXPECT_EQ(int_s2.empty(), 0);
}

TEST(Stack_Insert_Many, Insert_Many_Test) {
  s21::stack<int> int_s = {1, 2, 3};
  int_s.insert_many_back(4, 5, 6);
  EXPECT_EQ(int_s.size(), 6);
}
