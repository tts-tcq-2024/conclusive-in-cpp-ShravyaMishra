#include <gtest/gtest.h>
#include "typewise-alert.h"
#include <sstream>
#include <string>

// Helper function to capture stdout
std::string captureStdout(void (*func)()) {
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old);
    return oss.str();
}

// Test cases
TEST(AlertTestSuite, EvaluateBreach) {
    // Test for Passive Cooling
    EXPECT_EQ(evaluateBreach(-1, 0, 35), TOO_LOW);
    EXPECT_EQ(evaluateBreach(10, 0, 35), NORMAL);
    EXPECT_EQ(evaluateBreach(36, 0, 35), TOO_HIGH);

    // Test for High Active Cooling
    EXPECT_EQ(evaluateBreach(-1, 0, 45), TOO_LOW);
    EXPECT_EQ(evaluateBreach(20, 0, 45), NORMAL);
    EXPECT_EQ(evaluateBreach(46, 0, 45), TOO_HIGH);

    // Test for Medium Active Cooling
    EXPECT_EQ(evaluateBreach(-1, 0, 40), TOO_LOW);
    EXPECT_EQ(evaluateBreach(20, 0, 40), NORMAL);
    EXPECT_EQ(evaluateBreach(41, 0, 40), TOO_HIGH);
}

TEST(AlertTestSuite, CategorizeTemperature) {
    // Test for Passive Cooling
    EXPECT_EQ(categorizeTemperature(PASSIVE, -1), TOO_LOW);
    EXPECT_EQ(categorizeTemperature(PASSIVE, 10), NORMAL);
    EXPECT_EQ(categorizeTemperature(PASSIVE, 36), TOO_HIGH);

    // Test for High Active Cooling
    EXPECT_EQ(categorizeTemperature(HIGH_ACTIVE, -1), TOO_LOW);
    EXPECT_EQ(categorizeTemperature(HIGH_ACTIVE, 20), NORMAL);
    EXPECT_EQ(categorizeTemperature(HIGH_ACTIVE, 46), TOO_HIGH);

    // Test for Medium Active Cooling
    EXPECT_EQ(categorizeTemperature(MEDIUM_ACTIVE, -1), TOO_LOW);
    EXPECT_EQ(categorizeTemperature(MEDIUM_ACTIVE, 20), NORMAL);
    EXPECT_EQ(categorizeTemperature(MEDIUM_ACTIVE, 41), TOO_HIGH);
}

TEST(AlertTestSuite, SendsAlertsCorrectly) {
    // Set up BatteryInfo for testing
    BatteryInfo passiveCoolingBattery = {PASSIVE, "BrandX"};
    BatteryInfo highActiveCoolingBattery = {HIGH_ACTIVE, "BrandY"};

    // Capture output for EMAIL
    std::string output;

    // Test sending email for Passive Cooling
    output = captureStdout([&]() {
        triggerAlert(EMAIL, passiveCoolingBattery, -1);
    });
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos);

    output = captureStdout([&]() {
        triggerAlert(EMAIL, passiveCoolingBattery, 36);
    });
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos);

    // Test sending email for High Active Cooling
    output = captureStdout([&]() {
        triggerAlert(EMAIL, highActiveCoolingBattery, -1);
    });
    EXPECT_NE(output.find("Hi, the temperature is too low"), std::string::npos);

    output = captureStdout([&]() {
        triggerAlert(EMAIL, highActiveCoolingBattery, 46);
    });
    EXPECT_NE(output.find("Hi, the temperature is too high"), std::string::npos);

    // Test sending to controller
    output = captureStdout([&]() {
        triggerAlert(CONTROLLER, passiveCoolingBattery, 36);
    });
    EXPECT_NE(output.find("feed : 2"), std::string::npos); // 2 for TOO_HIGH
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
