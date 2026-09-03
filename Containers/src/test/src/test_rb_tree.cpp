#include <gtest/gtest.h>

#include "detail/rb_tree.hpp"
#include "s21_set.hpp"

TEST(RbTreeEdgeTest, CopyConstructorExceptionSafety) {
  s21::set<int> s1;
  for (int i = 0; i < 1000; ++i) {
    s1.insert(i);
  }

  s21::set<int> s2(s1);
  EXPECT_EQ(s2.size(), s1.size());
}

TEST(RbTreeEdgeTest, DeleteFixupCase1) {
  s21::set<int> s;

  s.insert(50);
  s.insert(30);
  s.insert(70);
  s.insert(20);
  s.insert(40);
  s.insert(60);
  s.insert(80);
  s.insert(10);
  s.insert(25);
  s.insert(35);
  s.insert(45);
  s.insert(55);
  s.insert(65);
  s.insert(75);
  s.insert(85);

  s.erase(s.find(10));
  s.erase(s.find(20));
  s.erase(s.find(25));
  s.erase(s.find(30));
  s.erase(s.find(35));

  EXPECT_TRUE(s.contains(40));
  EXPECT_TRUE(s.contains(50));
  EXPECT_TRUE(s.contains(60));
}

TEST(RbTreeEdgeTest, DeleteFixupCase3) {
  s21::set<int> s;

  s.insert(30);
  s.insert(20);
  s.insert(40);
  s.insert(10);
  s.insert(25);
  s.insert(35);
  s.insert(50);
  s.insert(5);
  s.insert(15);
  s.insert(28);

  s.erase(s.find(40));
  s.erase(s.find(35));
  s.erase(s.find(50));

  EXPECT_EQ(s.size(), 7);
}

TEST(RbTreeEdgeTest, PredecessorMaximum) {
  s21::set<int> s;

  s.insert(10);
  s.insert(5);
  s.insert(15);

  auto it = s.begin();
  --it;
  s.erase(s.find(5));
  s.erase(s.find(10));
  s.erase(s.find(15));

  EXPECT_TRUE(s.empty());
}

TEST(RbTreeEdgeTest, RbDeleteCase3Complex) {
  s21::set<int> s;

  s.insert(50);
  s.insert(30);
  s.insert(70);
  s.insert(20);
  s.insert(40);
  s.insert(60);
  s.insert(80);
  s.insert(35);
  s.insert(45);
  s.insert(65);

  s.erase(s.find(50));

  EXPECT_EQ(s.size(), 9);
  EXPECT_FALSE(s.contains(50));
  EXPECT_TRUE(s.contains(60));
}

TEST(RbTreeEdgeTest, RbDeleteWithNonNullX) {
  s21::set<int> s;

  s.insert(10);
  s.insert(5);
  s.insert(15);
  s.insert(3);
  s.insert(7);
  s.insert(12);
  s.insert(18);

  s.erase(s.find(3));
  s.erase(s.find(7));
  EXPECT_EQ(s.size(), 5);
}

TEST(RbTreeEdgeTest, DeleteFixupWithNonNullLeft) {
  s21::set<int> s;

  s.insert(30);
  s.insert(20);
  s.insert(40);
  s.insert(10);
  s.insert(25);
  s.insert(35);
  s.insert(50);
  s.insert(5);
  s.insert(15);
  s.insert(45);
  s.insert(55);

  s.erase(s.find(5));
  s.erase(s.find(15));
  s.erase(s.find(10));
  s.erase(s.find(20));

  EXPECT_EQ(s.size(), 7);
}

TEST(VectorEdgeTest, MoveOperatorSelfAssignment) {
  s21::vector<int> v{1, 2, 3};

  s21::vector<int>& ref = v;
  v = std::move(ref);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}