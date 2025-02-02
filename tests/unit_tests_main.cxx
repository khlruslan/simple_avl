#include "simple_adt.h"

#include <gtest/gtest.h>

namespace my {
  namespace project {
    namespace {

      TEST(AdtInt, Constructor) {
        auto dt = adt::Adt<int>{};
        EXPECT_EQ(true, true);
      }

    }  // namespace
  }  // namespace project
}  // namespace my

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
