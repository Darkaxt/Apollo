/**
 * @file tests/unit/test_video.cpp
 * @brief Test src/video.*.
 */
#include "../tests_common.h"

#include <src/video.h>

struct EncoderTest: PlatformTestSuite, testing::WithParamInterface<video::encoder_t *> {
  void SetUp() override {
    auto &encoder = *GetParam();
    if (!video::validate_encoder(encoder, false)) {
      // Encoder failed validation,
      // if it's software - fail, otherwise skip
      if (encoder.name == "software") {
        FAIL() << "Software encoder not available";
      } else {
        GTEST_SKIP() << "Encoder not available";
      }
    }
  }
};

INSTANTIATE_TEST_SUITE_P(
  EncoderVariants,
  EncoderTest,
  testing::Values(
#if !defined(__APPLE__)
    &video::nvenc,
#endif
#ifdef _WIN32
    &video::amdvce,
    &video::quicksync,
#endif
#ifdef __linux__
    &video::vaapi,
#endif
#ifdef __APPLE__
    &video::videotoolbox,
#endif
    &video::software
  ),
  [](const auto &info) {
    return std::string(info.param->name);
  }
);

TEST_P(EncoderTest, ValidateEncoder) {
  // todo:: test something besides fixture setup
}

TEST(DisplayRefreshTest, RetainsPreferredDisplayWhenItIsMissingAfterReenumeration) {
  std::vector<std::string> display_names {R"(\\.\DISPLAY5)"};
  const std::vector<std::string> old_display_names {R"(\\.\DISPLAY63)", R"(\\.\DISPLAY5)"};
  int current_display_index = 1;

  video::select_display_for_refresh(
    display_names,
    old_display_names,
    current_display_index,
    R"(\\.\DISPLAY63)",
    R"(\\.\DISPLAY63)",
    true
  );

  ASSERT_EQ(display_names.size(), 1);
  EXPECT_EQ(display_names[0], R"(\\.\DISPLAY63)");
  EXPECT_EQ(current_display_index, 0);
}

TEST(DisplayRefreshTest, FallsBackToFirstDisplayWhenNoPreferredDisplayIsPinned) {
  std::vector<std::string> display_names {R"(\\.\DISPLAY5)"};
  const std::vector<std::string> old_display_names {R"(\\.\DISPLAY63)", R"(\\.\DISPLAY5)"};
  int current_display_index = 1;

  video::select_display_for_refresh(
    display_names,
    old_display_names,
    current_display_index,
    R"(\\.\DISPLAY63)",
    R"(\\.\DISPLAY63)",
    false
  );

  ASSERT_EQ(display_names.size(), 1);
  EXPECT_EQ(display_names[0], R"(\\.\DISPLAY5)");
  EXPECT_EQ(current_display_index, 0);
}
