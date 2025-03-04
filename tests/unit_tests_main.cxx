#include "simple_adt.h"

#include <gtest/gtest.h>
#include <iterator>
#include <vector>

namespace my {
namespace project {
namespace {

TEST(AdtInt, Constructor) {
  auto dt = adt::Adt<int>{};
  EXPECT_EQ(dt.begin(), dt.end());
  EXPECT_EQ(dt.size(), 0);
}

TEST(AdtInt, InsertOneItem) {
  auto dt = adt::Adt<int>{};
  dt.insert(1);
  EXPECT_EQ(dt.size(), 1);
}

TEST(AdtInt, InsertOneItemLeft) {
  auto dt = adt::Adt<int>{};
  auto result = dt.insert(2);
  EXPECT_EQ(result.second, true);
  EXPECT_EQ(*result.first, 2);
  result = dt.insert(1);
  EXPECT_EQ(result.second, true);
  EXPECT_EQ(*result.first, 1);
  result = dt.insert(1);
  EXPECT_EQ(result.second, false);
  EXPECT_EQ(*result.first, 1);
  result = dt.insert(2);
  EXPECT_EQ(result.second, false);
  EXPECT_EQ(*result.first, 2);

  EXPECT_EQ(dt.size(), 2);
  std::vector<int> required_inorder = {1, 2};
  std::vector<int> required_balance = {0, -1};
  std::vector<int> required_preorder = {2, 1};
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertOneItemRight) {
  auto dt = adt::Adt<int>{};
  dt.insert(1);
  dt.insert(2);
  EXPECT_EQ(dt.size(), 2);
  std::vector<int> required_inorder = {1, 2};
  std::vector<int> required_balance = {1, 0};
  std::vector<int> required_preorder = {1, 2};
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTwoRight) {
  auto dt = adt::Adt<int>{};
  dt.insert(1);
  dt.insert(2);
  dt.insert(3);
  EXPECT_EQ(dt.size(), 3);
  std::vector<int> required_inorder = {1, 2, 3};
  std::vector<int> required_balance = {0, 0, 0};
  std::vector<int> required_preorder = {2, 1, 3};
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTwoLeft) {
  auto dt = adt::Adt<int>{};
  dt.insert(3);
  dt.insert(2);
  dt.insert(1);
  EXPECT_EQ(dt.size(), 3);
  std::vector<int> required_inorder = {1, 2, 3};
  std::vector<int> required_balance = {0, 0, 0};
  std::vector<int> required_preorder = {2, 1, 3};
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, BigTest1) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {0,  32, 1,  31, 2,  30, 3,  29, 4,  28, 5,
                             27, 6,  26, 7,  25, 8,  24, 9,  23, 10, 22,
                             11, 21, 12, 20, 13, 19, 14, 18, 15, 17};
  std::vector<int> required_preorder = {
      8,  4,  2,  1,  0,  3,  6,  5,  7,  21, 14, 11, 10, 9,  13, 12,
      19, 17, 15, 18, 20, 26, 23, 22, 24, 25, 29, 27, 28, 31, 30, 32};
  std::vector<int> required_inorder = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
      17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
  std::vector<int> required_balance = {0, -1, -1, 0, -1, 0, 0, 0,  1, 0, -1,
                                       0, 0,  -1, 0, 0,  0, 0, -1, 0, 0, 0,
                                       1, 1,  0,  0, 1,  0, 0, 0,  0, 0};
  for (auto a : source) {
    dt.insert(a);
  }
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate1) {
  /*
   * Test rotate 1
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 35};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 20;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {100, 25, 12,  20,  50,
                                        35,  75, 150, 125, 175};
  std::vector<int> required_inorder = {12, 20,  25,  35,  50,
                                       75, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {1, 0, 0, 0, 0, 0, -1, 0, 0, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate2) {
  /*
   * Test rotate 2
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 30, 60, 80};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 55;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {75, 50,  25, 12,  30,  60,
                                        55, 100, 80, 150, 125, 175};
  std::vector<int> required_inorder = {12, 25, 30,  50,  55,  60,
                                       75, 80, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate3) {
  /*
   * Test rotate 3
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 30, 60, 80};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 77;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {75,  50, 25, 12,  30,  60,
                                        100, 80, 77, 150, 125, 175};
  std::vector<int> required_inorder = {12, 25, 30,  50,  60,  75,
                                       77, 80, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate4) {
  /*
   * Test rotate 4
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 75;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {75, 50, 100};
  std::vector<int> required_balance = {0, 0, 0};
  std::vector<int> required_inorder = {50, 75, 100};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate5) {
  /*
   * Test rotate 5
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 120, 200};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 250;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {150, 100, 50, 120, 200, 250};
  std::vector<int> required_inorder = {50, 100, 120, 150, 200, 250};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {0, 0, 0, 0, 1, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate6) {
  /*
   * Test rotate 6
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 20, 120, 200, 110, 135, 170, 300};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 130;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {120, 100, 50,  20,  110, 150,
                                        135, 130, 200, 170, 300};
  std::vector<int> required_inorder = {20,  50,  100, 110, 120, 130,
                                       135, 150, 170, 200, 300};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {0, -1, -1, 0, 0, 0, -1, 0, 0, 0, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate7) {
  /*
   * Test rotate 7
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 150};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 125;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {125, 100, 150};
  std::vector<int> required_balance = {0, 0, 0};
  std::vector<int> required_inorder = {100, 125, 150};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, InsertTestRotate8) {
  /*
   * Test rotate 8
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 20, 120, 200, 110, 135, 170, 300};
  for (int a : source) {
    dt.insert(a);
  }
  int a = 105;
  dt.insert(a);
  source.push_back(a);
  std::vector<int> required_preorder = {120, 100, 50,  20,  110, 105,
                                        150, 135, 200, 170, 300};
  std::vector<int> required_inorder = {20,  50,  100, 105, 110, 120,
                                       135, 150, 170, 200, 300};
  EXPECT_EQ(dt.size(), source.size());
  auto preorder = dt.GetPreorderVector();
  auto inorder = dt.GetInorderVector();
  std::vector<int> required_balance = {0, -1, 0, 0, -1, 0, 0, 1, 0, 0, 0};
  auto avl_balance = dt.GetInorderAvlBalanceVector();
  EXPECT_EQ(required_balance, avl_balance);
  EXPECT_EQ(required_inorder, inorder);
  EXPECT_EQ(required_preorder, preorder);
}

TEST(AdtInt, IteratorIncrementTest) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50,  150, 20,  120, 200,
                             110, 135, 170, 300, 105};

  EXPECT_EQ(dt.begin(), dt.end());

  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {20,  50,  100, 105, 110, 120,
                                       135, 150, 170, 200, 300};
  EXPECT_EQ(dt.size(), source.size());
  std::vector<int> inorder;
  inorder.reserve(dt.size());

  for (auto it = dt.begin(), it_end = dt.end(); it != it_end; ++it) {
    inorder.emplace_back(*it);
  }

  EXPECT_EQ(required_inorder, inorder);
}

TEST(AdtInt, IteratorPostincrementTest) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50,  150, 20,  120, 200,
                             110, 135, 170, 300, 105};

  EXPECT_EQ(dt.begin(), dt.end());

  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {20,  50,  100, 105, 110, 120,
                                       135, 150, 170, 200, 300};

  EXPECT_EQ(dt.size(), source.size());
  std::vector<int> inorder;
  inorder.reserve(dt.size());

  auto it = dt.begin();
  auto it_end = dt.end();
  for (; it != it_end;) {
    inorder.emplace_back(*(it++));
  }

  EXPECT_EQ(required_inorder, inorder);
}

TEST(AdtInt, IteratorDecrementTest) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 20, 140, 160, 130, 155, 170, 10, 60};

  EXPECT_EQ(dt.begin(), dt.end());

  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {10,  20,  50,  60,  100, 130,
                                       140, 150, 155, 160, 170};
  EXPECT_EQ(dt.size(), source.size());
  auto inorder = dt.GetInorderVector();
  EXPECT_EQ(required_inorder, inorder);
  auto it = dt.begin();
  auto it_end = dt.end();
  for (; *it != required_inorder.back() && it != it_end; ++it) {
  }
  EXPECT_NE(it, dt.end());
  EXPECT_EQ(*it, required_inorder.back());

  std::vector<int> reverse_order;
  reverse_order.reserve(dt.size());

  it_end = dt.begin();

  for (; it != it_end; --it) {
    reverse_order.emplace_back(*it);
  }
  EXPECT_EQ(it_end, it);
  reverse_order.emplace_back(*it);

  std::reverse(required_inorder.begin(), required_inorder.end());

  EXPECT_EQ(required_inorder, reverse_order);
}

TEST(AdtInt, IteratorPostDecrementTest) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 20, 140, 160, 130, 155, 170, 10, 60};

  EXPECT_EQ(dt.begin(), dt.end());

  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {10,  20,  50,  60,  100, 130,
                                       140, 150, 155, 160, 170};
  EXPECT_EQ(dt.size(), source.size());
  auto inorder = dt.GetInorderVector();
  EXPECT_EQ(required_inorder, inorder);
  auto it = dt.begin();
  auto it_end = dt.end();
  for (; *it != required_inorder.back() && it != it_end; ++it) {
  }
  EXPECT_NE(it, dt.end());
  EXPECT_EQ(*it, required_inorder.back());

  std::vector<int> reverse_order;
  reverse_order.reserve(dt.size());

  it_end = dt.begin();

  for (; it != it_end;) {
    reverse_order.emplace_back(*(it--));
  }
  EXPECT_EQ(it_end, it);
  reverse_order.emplace_back(*it);

  std::reverse(required_inorder.begin(), required_inorder.end());

  EXPECT_EQ(required_inorder, reverse_order);
}

TEST(AdtInt, IteratorIteratorTraitsTest) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50,  150, 20,  120, 200,
                             110, 135, 170, 300, 105};

  EXPECT_EQ(typeid(typename std::iterator_traits<
                   adt::Adt<int>::iterator>::iterator_category),
            typeid(std::bidirectional_iterator_tag));
}

TEST(AdtInt, LowerBoundEmpty) {
  auto dt = adt::Adt<int>{};
  auto it = dt.lower_bound(42);
  EXPECT_EQ(dt.end(), it);
}

TEST(AdtInt, LowerBound) {
  /*
   * Test lower_bound
   */
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 35, 20};
  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {12, 20,  25,  35,  50,
                                       75, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto inorder = dt.GetInorderVector();
  EXPECT_EQ(required_inorder, inorder);
  auto it = dt.lower_bound(11);
  EXPECT_EQ(*it, 12);
  it = dt.lower_bound(13);
  EXPECT_EQ(*it, 20);
  it = dt.lower_bound(25);
  EXPECT_EQ(*it, 25);
  it = dt.lower_bound(102);
  EXPECT_EQ(*it, 125);
  it = dt.lower_bound(99);
  EXPECT_EQ(*it, 100);
  it = dt.lower_bound(180);
  EXPECT_EQ(it, dt.end());
}

TEST(AdtInt, UpperBound) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 35, 20};
  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {12, 20,  25,  35,  50,
                                       75, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto inorder = dt.GetInorderVector();
  EXPECT_EQ(required_inorder, inorder);
  auto it = dt.upper_bound(11);
  EXPECT_EQ(*it, 12);
  it = dt.upper_bound(12);
  EXPECT_EQ(*it, 20);
  it = dt.upper_bound(21);
  EXPECT_EQ(*it, 25);
  it = dt.upper_bound(100);
  EXPECT_EQ(*it, 125);
  it = dt.upper_bound(99);
  EXPECT_EQ(*it, 100);
  it = dt.upper_bound(180);
  EXPECT_EQ(it, dt.end());
}

TEST(AdtInt, DecrementEndIterator) {
  auto dt = adt::Adt<int>{};
  std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 35, 20};
  for (int a : source) {
    dt.insert(a);
  }
  std::vector<int> required_inorder = {12, 20,  25,  35,  50,
                                       75, 100, 125, 150, 175};
  EXPECT_EQ(dt.size(), source.size());
  auto inorder = dt.GetInorderVector();
  EXPECT_EQ(required_inorder, inorder);
  auto it = dt.end();
  --it;
  EXPECT_EQ(*it, 175);
  it--;
  EXPECT_EQ(*it, 150);
}

} // namespace
} // namespace project
} // namespace my

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
