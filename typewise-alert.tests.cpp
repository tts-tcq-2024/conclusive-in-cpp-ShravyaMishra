#include "typewise-alert.h"
#include <gtest/gtest.h>

// Test to check the inferBreach function with different scenarios
TEST(TypewiseAlertTest, InferBreach) {
    EXPECT_EQ(TypewiseAlert::evaluateBreach(25, 20, 30), TypewiseAlert::BreachType::NORMAL);
    EXPECT_EQ(TypewiseAlert::evaluateBreach(15, 20, 30), TypewiseAlert::BreachType::TOO_LOW);
    EXPECT_EQ(TypewiseAlert::evaluateBreach(35, 20, 30), TypewiseAlert::BreachType::TOO_HIGH);
}

// Test to verify the classifyTemperatureBreach function for different cooling types
TEST(TypewiseAlertTest, ClassifyTemperatureBreach) {
    EXPECT_EQ(TypewiseAlert::classifyTemperature(30, TypewiseAlert::CoolingType::PASSIVE_COOLING), TypewiseAlert::BreachType::NORMAL);
    EXPECT_EQ(TypewiseAlert::classifyTemperature(40, TypewiseAlert::CoolingType::PASSIVE_COOLING), TypewiseAlert::BreachType::TOO_HIGH);
    EXPECT_EQ(TypewiseAlert::classifyTemperature(50, TypewiseAlert::CoolingType::HI_ACTIVE_COOLING), TypewiseAlert::BreachType::TOO_HIGH);
    EXPECT_EQ(TypewiseAlert::classifyTemperature(-5, TypewiseAlert::CoolingType::MED_ACTIVE_COOLING), TypewiseAlert::BreachType::TOO_LOW);
}

// Mocking a test for sending alerts to the controller
TEST(TypewiseAlertTest, CheckAndAlertToController) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    TypewiseAlert::BatteryCharacter batteryChar = { TypewiseAlert::CoolingType::PASSIVE_COOLING, "BrandA" };
    TypewiseAlert::monitorAndAlert(TypewiseAlert::AlertTarget::TO_CONTROLLER, batteryChar, 50);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  // TOO_HIGH is expected to be 2
}

// Mocking a test for sending alerts to email
TEST(TypewiseAlertTest, CheckAndAlertToEmail) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    TypewiseAlert::BatteryCharacter batteryChar = { TypewiseAlert::CoolingType::PASSIVE_COOLING, "BrandA" };
    TypewiseAlert::monitorAndAlert(TypewiseAlert::AlertTarget::TO_EMAIL, batteryChar, 50);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

// Test to ensure normal temperatures do not trigger alerts
TEST(TypewiseAlertTest, NoAlertForNormalTemperature) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    TypewiseAlert::BatteryCharacter batteryChar = { TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, "BrandB" };
    TypewiseAlert::monitorAndAlert(TypewiseAlert::AlertTarget::TO_EMAIL, batteryChar, 40);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  // Expect no output since temperature is normal
}
