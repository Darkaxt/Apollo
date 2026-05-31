/**
 * @file tests/unit/test_process.cpp
 * @brief Test src/process.*.
 */
#include "../tests_common.h"

#include <src/process.h>

TEST(VirtualDisplayLaunchTest, ExplicitClientVirtualDisplayRequestCannotFallBackToPhysicalDisplay) {
  EXPECT_TRUE(proc::should_abort_on_virtual_display_failure(false, true, false));
}

TEST(VirtualDisplayLaunchTest, AppVirtualDisplayRequirementCannotFallBackToPhysicalDisplay) {
  EXPECT_TRUE(proc::should_abort_on_virtual_display_failure(false, false, true));
}

TEST(VirtualDisplayLaunchTest, HeadlessModeCannotFallBackToPhysicalDisplay) {
  EXPECT_TRUE(proc::should_abort_on_virtual_display_failure(true, false, false));
}

TEST(VirtualDisplayLaunchTest, EncoderProbeOnlyCanContinueWithoutVirtualDisplay) {
  EXPECT_FALSE(proc::should_abort_on_virtual_display_failure(false, false, false));
}
