#include "simple_adt.h"

#include <vector>
#include <gtest/gtest.h>

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
        dt.probe(1);
        EXPECT_EQ(dt.size(), 1);
      }

      TEST(AdtInt, InsertOneItemLeft) {
        auto dt = adt::Adt<int>{};
        dt.probe(2);
        dt.probe(1);
        EXPECT_EQ(dt.size(), 2);
        std::vector<int> required_inorder = {1, 2};
        std::vector<int> required_preorder = {2, 1};
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertOneItemRight) {
        auto dt = adt::Adt<int>{};
        dt.probe(1);
        dt.probe(2);
        EXPECT_EQ(dt.size(), 2);
        std::vector<int> required_inorder = {1, 2};
        std::vector<int> required_preorder = {1, 2};
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTwoRight) {
        auto dt = adt::Adt<int>{};
        dt.probe(1);
        dt.probe(2);
        dt.probe(3);
        EXPECT_EQ(dt.size(), 3);
        std::vector<int> required_inorder = {1, 2, 3};
        std::vector<int> required_preorder = {2, 1, 3};
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTwoLeft) {
        auto dt = adt::Adt<int>{};
        dt.probe(3);
        dt.probe(2);
        dt.probe(1);
        EXPECT_EQ(dt.size(), 3);
        std::vector<int> required_inorder = {1, 2, 3};
        std::vector<int> required_preorder = {2, 1, 3};
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, BigTest1) {
        auto dt = adt::Adt<int>{};
        std::vector<int> source = {0, 32, 1, 31, 2, 30, 3, 29, 4, 28, 5, 27, 6, 26, 7, 25, 8, 24, 9, 23, 10, 22, 11, 21, 12, 20, 13, 19, 14, 18, 15, 17};
        std::vector<int> required_preorder = {8, 4, 2, 1, 0, 3, 6, 5, 7, 21, 14, 11, 10, 9, 13, 12, 19, 17, 15, 18, 20, 26, 23, 22, 24, 25, 29, 27, 28, 31, 30, 32};
        std::vector<int> required_inorder = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
        for (auto a:source){
          dt.probe(a);
        }
        EXPECT_EQ(dt.size(), source.size());
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTestRotate1) {
        /*
         * Test rotate 1
         */
        auto dt = adt::Adt<int>{};
        std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 35};
        for (int a : source){
          dt.probe(a);
        }
        dt.probe(20);
        std::vector<int> required_preorder = {100, 25, 12, 20, 50, 35, 75, 150, 125, 175};
        std::vector<int> required_inorder = {12, 20, 25, 35, 50, 75, 100, 125, 150, 175};
        EXPECT_EQ(dt.size(), source.size() + 1);
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTestRotate2) {
        /*
         * Test rotate 2
         */
        auto dt = adt::Adt<int>{};
        std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 30, 60, 80} ;
        for (int a : source){
          dt.probe(a);
        }
        dt.probe(55);
        std::vector<int> required_preorder = {75, 50, 25, 12, 30, 60, 55, 100, 80, 150, 125, 175};
        std::vector<int> required_inorder = {12, 25, 30, 50, 55, 60, 75, 80, 100, 125, 150, 175};
        EXPECT_EQ(dt.size(), source.size() + 1);
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTestRotate3) {
        /*
         * Test rotate 3
         */
        auto dt = adt::Adt<int>{};
        std::vector<int> source = {100, 50, 150, 25, 75, 125, 175, 12, 30, 60, 80} ;
        for (int a : source){
          dt.probe(a);
        }
        dt.probe(77);
        std::vector<int> required_preorder = {75, 50, 25, 12, 30, 60, 100, 80, 77, 150, 125, 175};
        std::vector<int> required_inorder = {12, 25, 30, 50, 60, 75, 77, 80, 100, 125, 150, 175};
        EXPECT_EQ(dt.size(), source.size() + 1);
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }

      TEST(AdtInt, InsertTestRotate4) {
        /*
         * Test rotate 4
         */
        auto dt = adt::Adt<int>{};
        std::vector<int> source = {100, 50} ;
        for (int a : source){
          dt.probe(a);
        }
        dt.probe(75);
        std::vector<int> required_preorder = {75, 50, 100};
        std::vector<int> required_inorder = {50, 75, 100};
        EXPECT_EQ(dt.size(), source.size() + 1);
        auto preorder = dt.GetPreorderVector();
        auto inorder = dt.GetInorderVector();
        EXPECT_EQ(required_inorder, inorder);
        EXPECT_EQ(required_preorder, preorder);
      }
    }  // namespace
  }  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
