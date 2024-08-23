#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    // Test for too low breach
    EXPECT_EQ(inferBreach(10, 20, 30), TOO_LOW);

    // Test for too high breach
    EXPECT_EQ(inferBreach(40, 20, 30), TOO_HIGH);

    // Test for normal range
    EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);

    // Test edge case: value equal to lower limit
    EXPECT_EQ(inferBreach(20, 20, 30), NORMAL);

    // Test edge case: value equal to upper limit
    EXPECT_EQ(inferBreach(30, 20, 30), NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    // Test for PASSIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 34), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);

    // Test for HI_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0), NORMAL);

    // Test for MED_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToController) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 36);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmail) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 36);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");

    // Testing for normal temperature
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 34);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is normal\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
