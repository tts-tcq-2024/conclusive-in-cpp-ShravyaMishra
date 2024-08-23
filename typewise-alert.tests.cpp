#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(10, 20, 30), TOO_LOW);
    EXPECT_EQ(inferBreach(40, 20, 30), TOO_HIGH);
    EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToController) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 36);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  // Removed the leading "0x" in the output expectation
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmail) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING};
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
