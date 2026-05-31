/**
 * @file tests/unit/test_virtual_display.cpp
 * @brief Test Windows virtual display helpers.
 */
#include "../tests_common.h"

#ifdef _WIN32
#include <src/platform/windows/virtual_display.h>

TEST(VirtualDisplayConfigFlagsTest, ActiveQueriesAreVirtualModeAware) {
  EXPECT_NE(VDISPLAY::activeDisplayConfigQueryFlags() & QDC_VIRTUAL_MODE_AWARE, 0u);
}

TEST(VirtualDisplayConfigFlagsTest, SuppliedApplyUsesVirtualModeAware) {
  EXPECT_NE(VDISPLAY::suppliedDisplayConfigApplyFlags() & SDC_VIRTUAL_MODE_AWARE, 0u);
}

#endif
