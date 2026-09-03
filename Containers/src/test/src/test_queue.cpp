#include <gtest/gtest.h>

#include <stdexcept>

#include "s21_queue.hpp"

TEST(Queue_Constructor, Default) {
  s21::queue<int> int_q;
  s21::queue<double> double_q;

  EXPECT_EQ(int_q.empty(), 1);
  EXPECT_EQ(double_q.empty(), 1);
}

TEST(Queue_Constructor, Initializer_List) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.empty(), 0);
}

TEST(Queue_Constructor, Copy) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Constructor, Move) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(std::move(int_q1));

  EXPECT_EQ(int_q2.empty(), 0);
  EXPECT_EQ(int_q1.empty(), 1);
}

TEST(Queue_Constructor, Operator_eq_movement) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;
  int_q2 = std::move(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Constructor, Operator_eq_copy) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;
  int_q2 = int_q1;

  EXPECT_EQ(int_q2.size(), int_q1.size());
  EXPECT_EQ(int_q2.front(), int_q1.front());
}

//-- element access --//

TEST(Queue_Element_Access, Front) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.front(), 1);
}

TEST(Queue_Element_Access, Front_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.front(), std::out_of_range);
}

TEST(Queue_Element_Access, Back) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.back(), 3);
}

TEST(Queue_Element_Access, Back_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.back(), std::out_of_range);
}

// capacity

TEST(Queue_Capacity, Empty) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);
}

TEST(Queue_Capacity, Size) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.size(), 3);
  EXPECT_EQ(int_q2.size(), 0);
}

// modifiers

TEST(Queue_Modifiers, Push) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.push(7);

  EXPECT_EQ(int_q.size(), 4);
  EXPECT_EQ(int_q.back(), 7);
}

TEST(Queue_Modifiers, Push_Empty) {
  s21::queue<int> int_q;
  int_q.push(7);

  EXPECT_EQ(int_q.empty(), 0);
  EXPECT_EQ(int_q.size(), 1);
}

TEST(Queue_Modifiers, Pop) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.pop();

  EXPECT_EQ(int_q.front(), 2);
}

TEST(Queue_Modifiers, Pop_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.pop(), std::out_of_range);
}

TEST(Queue_Modifiers, Swap) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);

  int_q1.swap(int_q2);

  EXPECT_EQ(int_q1.empty(), 1);
  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Insert_Many, Insert_Many_Back) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.insert_many_back(4, 5, 6);

  EXPECT_EQ(int_q.size(), 6);
  EXPECT_EQ(int_q.back(), 6);
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> queue;

  EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, InitializerListConstructor_EmptyQueue) {
  s21::queue<int> queue = {};

  EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, InitializerListConstructor_NonEmptyQueue) {
  s21::queue<int> queue = {1, 2, 3, 4, 5};

  EXPECT_EQ(queue.size(), 5);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 5);
}

TEST(QueueTest, CopyConstructor_EmptyQueue) {
  s21::queue<int> queue;

  s21::queue<int> copy{queue};

  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(copy.empty());
}

TEST(QueueTest, CopyConstructor_NonEmptyQueue) {
  s21::queue<int> queue{4, 2, 3, 7, 9};

  s21::queue<int> copy{queue};

  EXPECT_EQ(queue.size(), 5);
  EXPECT_EQ(queue.front(), 4);
  EXPECT_EQ(queue.back(), 9);
  EXPECT_EQ(copy.size(), 5);
  EXPECT_EQ(copy.front(), 4);
  EXPECT_EQ(copy.back(), 9);
}

TEST(QueueTest, MoveConstructor_EmptyQueue) {
  s21::queue<int> queue;

  s21::queue<int> dist{std::move(queue)};

  EXPECT_TRUE(dist.empty());
}

TEST(QueueTest, MoveConstructor_NonEmptyQueue) {
  s21::queue<int> queue{2, 9, 3, 7, 4};

  s21::queue<int> dist(std::move(queue));

  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(dist.size(), 5);
  EXPECT_EQ(dist.front(), 2);
  EXPECT_EQ(dist.back(), 4);
}

TEST(QueueTest, MoveAssignmentOperator) {
  // s21::queue<int> queue1{1, 2, 3};
  // s21::queue<int> queue2{4, 5};

  // queue1 = queue2;

  // EXPECT_EQ(queue1.size(), 2);
  // EXPECT_EQ(queue1.front(), 4);
  // EXPECT_EQ(queue1.back(), 5);
  // EXPECT_EQ(queue2.size(), 2);
  // EXPECT_EQ(queue2.front(), 4);
  // EXPECT_EQ(queue2.back(), 5);
}

TEST(QueueTest, CopyAssignmentOperator) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2{4, 5};

  queue2 = std::move(queue1);

  EXPECT_TRUE(queue1.empty());
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 3);
}

TEST(QueueTest, Empty) {
  s21::queue<int> queue1{1};
  s21::queue<int> queue2;

  EXPECT_FALSE(queue1.empty());
  EXPECT_TRUE(queue2.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> queue{1, 2, 3, 4, 5, 6, 7, 8};

  EXPECT_EQ(queue.size(), 8);
}

TEST(QueueTest, Push_EmptyQueue) {
  s21::queue<int> queue;
  const int number = 8;

  queue.push(number);
  queue.push(4);

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.front(), 8);
  EXPECT_EQ(queue.back(), 4);
}

TEST(QueueTest, Push_NonEmptyQueue) {
  s21::queue<int> queue{1, 2, 3, 4, 5, 6};

  queue.push(7);
  queue.push(8);

  EXPECT_EQ(queue.size(), 8);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 8);
}

TEST(QueueTest, Pop) {
  s21::queue<int> queue{1, 2, 3, 4, 5, 6, 7, 8};

  queue.pop();
  queue.pop();

  EXPECT_EQ(queue.size(), 6);
  EXPECT_EQ(queue.front(), 3);
  EXPECT_EQ(queue.back(), 8);
}

TEST(QueueTest, Swap_NonEmptyWithNonEmptyQueue) {
  s21::queue<int> queue1{1, 2, 3, 4, 5};
  s21::queue<int> queue2{6, 7, 8, 9};

  queue1.swap(queue2);

  EXPECT_EQ(queue1.size(), 4);
  EXPECT_EQ(queue1.front(), 6);
  EXPECT_EQ(queue1.back(), 9);
  EXPECT_EQ(queue2.size(), 5);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 5);
}

TEST(QueueTest, Swap_EmptyWithNonEmptyQueue) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2;

  queue1.swap(queue2);

  EXPECT_TRUE(queue1.empty());
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 3);
}

TEST(QueueTest, InsertManyBack_EmptyQyeye) {
  s21::queue<int> queue;

  queue.insert_many_back(1, 2, 3);

  EXPECT_EQ(queue.size(), 3);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);
}

TEST(QueueTest, InsertManyBack_NonEmptyQyeye) {
  s21::queue<int> queue{1, 2};

  queue.insert_many_back(3, 4);

  EXPECT_EQ(queue.size(), 4);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 4);
}