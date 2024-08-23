#include "battery-alert-system.h"
#include <gtest/gtest.h>

// Test to check the inferBreach function with different scenarios
TEST(BatteryAlertSystemTest, InferBreach) {
    EXPECT_EQ(BatteryAlertSystem::inferBreach(25, 20, 30), BatteryAlertSystem::BreachType::NORMAL);
    EXPECT_EQ(BatteryAlertSystem::inferBreach(15, 20, 30), BatteryAlertSystem::BreachType::TOO_LOW);
    EXPECT_EQ(BatteryAlertSystem::inferBreach(35, 20, 30), BatteryAlertSystem::BreachType::TOO_HIGH);
}

// Test to verify the classifyTemperatureBreach function for different cooling types
TEST(BatteryAlertSystemTest, ClassifyTemperatureBreach) {
    EXPECT_EQ(BatteryAlertSystem::classifyTemperatureBreach(BatteryAlertSystem::CoolingType::PASSIVE_COOLING, 30), BatteryAlertSystem::BreachType::NORMAL);
    EXPECT_EQ(BatteryAlertSystem::classifyTemperatureBreach(BatteryAlertSystem::CoolingType::PASSIVE_COOLING, 40), BatteryAlertSystem::BreachType::TOO_HIGH);
    EXPECT_EQ(BatteryAlertSystem::classifyTemperatureBreach(BatteryAlertSystem::CoolingType::HI_ACTIVE_COOLING, 50), BatteryAlertSystem::BreachType::TOO_HIGH);
    EXPECT_EQ(BatteryAlertSystem::classifyTemperatureBreach(BatteryAlertSystem::CoolingType::MED_ACTIVE_COOLING, -5), BatteryAlertSystem::BreachType::TOO_LOW);
}

// Mocking a test for sending alerts to the controller
TEST(BatteryAlertSystemTest, CheckAndAlertToController) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    BatteryAlertSystem::BatteryCharacter batteryChar = { BatteryAlertSystem::CoolingType::PASSIVE_COOLING, "BrandA" };
    BatteryAlertSystem::checkAndAlert(BatteryAlertSystem::AlertTarget::TO_CONTROLLER, batteryChar, 50);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  // TOO_HIGH is expected to be 2
}

// Mocking a test for sending alerts to email
TEST(BatteryAlertSystemTest, CheckAndAlertToEmail) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    BatteryAlertSystem::BatteryCharacter batteryChar = { BatteryAlertSystem::CoolingType::PASSIVE_COOLING, "BrandA" };
    BatteryAlertSystem::checkAndAlert(BatteryAlertSystem::AlertTarget::TO_EMAIL, batteryChar, 50);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

// Test to ensure normal temperatures do not trigger alerts
TEST(BatteryAlertSystemTest, NoAlertForNormalTemperature) {
    // Redirect stdout to a stringstream to check output
    testing::internal::CaptureStdout();
    
    BatteryAlertSystem::BatteryCharacter batteryChar = { BatteryAlertSystem::CoolingType::HI_ACTIVE_COOLING, "BrandB" };
    BatteryAlertSystem::checkAndAlert(BatteryAlertSystem::AlertTarget::TO_EMAIL, batteryChar, 40);
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  // Expect no output since temperature is normal
}
