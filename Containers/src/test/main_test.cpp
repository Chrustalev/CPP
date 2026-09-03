#include <gtest/gtest.h>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(test_of_test, test_name) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
