#include <gtest/gtest.h>

#include "s21_multiset.hpp"
#include "s21_set.hpp"

//---------------- FIRST ATTEMPT ----------------//

//---------------- SECOND ATTEMPT ----------------//

TEST(multiset, allcase) {
  s21::multiset<int> my_multiset;
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  EXPECT_EQ(my_multiset.size(), 10U);
  auto it = my_multiset.begin();
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 9U);
  it = my_multiset.begin();
  EXPECT_EQ(*it, 10);
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 8U);
}

//---------------- THIRD ATTEMPT ----------------//

TEST(S21multisetTest, DefaultConstructor) {
  s21::multiset<int> miltiset;
  ASSERT_TRUE(miltiset.empty());
  ASSERT_EQ(0U, miltiset.size());
  EXPECT_EQ(miltiset.size(), 0U);
}

TEST(S21multisetTest, InitializerListConstructor) {
  s21::multiset<int> ms1({1, 2, 3, 2, 4, 2});
  ASSERT_FALSE(ms1.empty());
  ASSERT_EQ(6U, ms1.size());
}

TEST(S21multisetTest, CopyConstructor) {
  s21::multiset<int> set({1, 2, 3, 2});
  s21::multiset<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21multisetTest, MoveConstructor) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> move(std::move(multiset));
  ASSERT_TRUE(multiset.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(S21multisetTest, AssignmentOperator1) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = multiset1;
  ASSERT_FALSE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(multiset1.size(), multiset2.size());
}

TEST(S21multisetTest, AssignmentOperator2) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = std::move(multiset1);
  ASSERT_TRUE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(3U, multiset2.size());
}

TEST(S21multisetTest, IteratorBegin) {
  s21::multiset<int> multiset({1, 2, 3, 1, 5});
  s21::multiset<int>::iterator iterat;
  iterat = multiset.begin();
  s21::set<int>::iterator itFind;
  itFind = multiset.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(S21multisetTest, CapacityEmpty) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  ASSERT_FALSE(multiset.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21multisetTest, CapacitySize) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  EXPECT_EQ(multiset.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(S21multisetTest, ModifierClear) {
  s21::multiset<int> multiset({1, 2, 3});
  ASSERT_FALSE(multiset.empty());
  multiset.clear();
  ASSERT_TRUE(multiset.empty());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(S21multisetTest, ModifierInsert1) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  set.insert(5);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21multisetTest, ModifierInsert2) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21multisetTest, ModifierErase) {
  s21::multiset<int> set = {1, 2, 3, 2};
  EXPECT_EQ(set.size(), 4U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_TRUE(set.contains(2));
}

TEST(S21multisetTest, ModifierSwap) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {4, 5, 6};
  multiset1.swap(multiset2);
  EXPECT_EQ(multiset1.size(), 3U);
  EXPECT_EQ(multiset2.size(), 3U);
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
  ASSERT_TRUE(multiset1.contains(6));
  ASSERT_TRUE(multiset2.contains(1));
  ASSERT_TRUE(multiset2.contains(2));
  ASSERT_TRUE(multiset2.contains(3));
}

TEST(S21multisetTest, ModifierMerge) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {3, 4, 5};
  multiset1.merge(multiset2);
  EXPECT_EQ(multiset1.size(), 6U);
  EXPECT_EQ(multiset2.size(), 0U);
  ASSERT_TRUE(multiset1.contains(1));
  ASSERT_TRUE(multiset1.contains(2));
  ASSERT_TRUE(multiset1.contains(3));
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
}

TEST(S21multisetTest, LookupCount) {
  s21::multiset<int> multiset = {1, 2, 3, 2, 3, 7, 2};
  EXPECT_EQ(multiset.size(), 7U);
  EXPECT_EQ(multiset.count(2), 3U);
  EXPECT_EQ(multiset.count(3), 2U);
  EXPECT_EQ(multiset.count(10), 0U);
}

TEST(S21multisetTest, LookupEqualRange) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto range = multiset.equal_range(3);
  ASSERT_EQ(*range.first, 3);
  ASSERT_EQ(*range.second, 7);
  range = multiset.equal_range(7);
  ASSERT_EQ(*range.first, 7);
  ASSERT_EQ(range.second, multiset.end());
  range = multiset.equal_range(8);
  ASSERT_EQ(range.first, multiset.end());
  ASSERT_EQ(range.second, multiset.end());
}

TEST(S21multisetTest, LookupLowerBound) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.lower_bound(3);
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 7);
}

TEST(S21multisetTest, LookupUpperBound) {
  s21::multiset<int> multiset = {1, 7, 3, 3, 2};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.upper_bound(3);
  ASSERT_EQ(*it, 7);
}

// ==================== MULTISET TESTS ====================
TEST(MultisetInsertManyTest, InsertMany_Basic) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(10, 20, 10, 30, 10);

  EXPECT_EQ(results.size(), 5);
  EXPECT_EQ(ms.size(), 5);

  for (const auto& it : results) {
    EXPECT_NE(it, ms.end());
  }

  EXPECT_EQ(ms.count(10), 3);
  EXPECT_EQ(ms.count(20), 1);
  EXPECT_EQ(ms.count(30), 1);
}

TEST(MultisetInsertManyTest, InsertMany_Strings) {
  s21::multiset<std::string> ms;

  auto results = ms.insert_many("apple", "banana", "apple", "apple", "cherry");

  EXPECT_EQ(results.size(), 5);
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count("apple"), 3);
  EXPECT_EQ(ms.count("banana"), 1);
  EXPECT_EQ(ms.count("cherry"), 1);
}

TEST(MultisetInsertManyTest, InsertMany_EmptyArgs) {
  s21::multiset<int> ms{1, 2, 3};

  auto results = ms.insert_many();

  EXPECT_EQ(results.size(), 0);
  EXPECT_EQ(ms.size(), 3);
}

TEST(MultisetInsertManyEdgeTest, InsertMany_ManyDuplicates) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(1, 1, 1, 2, 2, 3);

  EXPECT_EQ(results.size(), 6);
  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(ms.count(1), 3);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
}

TEST(MultisetInsertManyEdgeTest, InsertMany_LargeNumber) {
  s21::multiset<int> ms;

  const int count = 50;

  auto results = ms.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
                                27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                                39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50);

  EXPECT_EQ(results.size(), count);
  EXPECT_EQ(ms.size(), count);
}
