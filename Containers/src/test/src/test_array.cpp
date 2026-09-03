#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "s21_array.hpp"

// TODO: TEST(Array_Constructor, Default_Empty), ошибка array<int, 0>
// error: ISO C++ forbids zero-size array

TEST(Array_Constructor, Default_Empty) {
  // s21::array<int, 0> temp;
  // EXPECT_EQ(temp.empty(), 1);
}

TEST(Array_Constructor, Default_Not_Empty) {
  s21::array<double, 5> temp;

  EXPECT_EQ(temp.empty(), 0);
}

TEST(Array_Constructor, Initializer_List) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.size(), 3);
}

TEST(Array_Constructor, Copy) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> copy(temp);

  EXPECT_EQ(copy.size(), 3);
}

TEST(Array_Constructor, Move) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> move(std::move(temp));

  EXPECT_EQ(temp.empty(), 1);
  EXPECT_EQ(move.size(), 3);
}

TEST(Array_Constructor, Operator_Eq_Movement) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> move;
  move = std::move(temp);

  EXPECT_EQ(move.size(), 3);
}

TEST(Array_Constructor, Operator_Eq_Copy) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> copy;
  copy = temp;

  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(temp[0], copy[0]);
  EXPECT_EQ(temp[1], copy[1]);
  EXPECT_EQ(temp[2], copy[2]);
}

//-- element access --//

TEST(Array_Element_Access, At) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.at(1), 2);
}

TEST(Array_Element_Access, At_OutOfRange) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_THROW(temp.at(7), std::out_of_range);
}

TEST(Array_Element_Access, Operator_At) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp[1], 2);
}

TEST(Array_Element_Access, Front) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.front(), 1);
}

TEST(Array_Element_Access, Back) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.back(), 3);
}

TEST(Array_Element_Access, Data) {
  s21::array<int, 3> temp = {1, 2, 3};
  int* value = temp.data();

  EXPECT_EQ(value[0], 1);
}

TEST(Array_Iterators, Begin) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(*(temp.begin()), 1);
}

TEST(Array_Iterators, End) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.end(), temp.begin() + 3);
}

TEST(Array_Capacity, Empty) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.empty(), 0);
}

TEST(Array_Capacity, Size) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.size(), 3);
}

TEST(Array_Capacity, Max_Size) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.max_size(), 3);
}

TEST(Array_Modifiers, Swap) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> temp2 = {4, 5, 6};
  temp.swap(temp2);

  EXPECT_EQ(temp.front(), 4);
  EXPECT_EQ(temp.back(), 6);
  EXPECT_EQ(temp2.front(), 1);
  EXPECT_EQ(temp2.back(), 3);
}

TEST(Array_Modifiers, Fill) {
  s21::array<int, 3> temp = {1, 2, 3};
  temp.fill(5);

  EXPECT_EQ(temp.front(), 5);
  EXPECT_EQ(temp.back(), 5);
}

TEST(ArrayTest, BigInitListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  s21::array<int, 5> copy(arr);

  EXPECT_EQ(copy.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(copy[i], arr[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  s21::array<int, 5> dist(std::move(arr));

  EXPECT_EQ(dist.size(), 5);
  EXPECT_EQ(dist[3], 4);
  EXPECT_EQ(dist[4], 5);
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 0};

  arr1 = std::move(arr2);

  EXPECT_EQ(arr1[1], 7);
  EXPECT_EQ(arr1[4], 0);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 0};

  arr1 = std::move(arr2);

  EXPECT_EQ(arr1[0], 6);
  EXPECT_EQ(arr1[3], 9);
}

TEST(ArrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  auto it = arr.begin();
  *it = 10;

  EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  auto it = std::prev(arr.end());

  EXPECT_EQ(*it, 5);
}

TEST(ArrayTest, DataTest) {
  s21::array<int, 3> arr = {1, 2, 3};

  int* q = arr.data();
  q[1] = 8;

  EXPECT_EQ(arr[1], 8);
}

TEST(ArrayTest, At_ValidIndex) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  int value = arr.at(2);

  EXPECT_EQ(value, 3);
}

TEST(ArrayTest, At_OutOfBounds) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  arr[2] = 7;

  EXPECT_EQ(arr[2], 7);
}

TEST(ArrayTest, ConstOperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  int value = arr.front();

  EXPECT_EQ(value, 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  int value = arr.back();

  EXPECT_EQ(value, 5);
}

TEST(ArrayTest, Empty_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, Size_NonEmptyArray) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 5> arr;

  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 0};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[2], 8);
  EXPECT_EQ(arr1[4], 0);
  EXPECT_EQ(arr2[3], 4);
  EXPECT_EQ(arr2[4], 5);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;

  arr.fill(9);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 9);
  }
}