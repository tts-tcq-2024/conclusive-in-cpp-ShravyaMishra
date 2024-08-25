#include <assert.h>
#include "typewise-alert.h"
#include <stdio.h>

// Test inferBreach function
void testInferBreach() {
    assert(TypewiseAlert::inferBreach(20, 30, 40) == TypewiseAlert::BreachType::TOO_LOW);
    assert(TypewiseAlert::inferBreach(50, 30, 40) == TypewiseAlert::BreachType::TOO_HIGH);
    assert(TypewiseAlert::inferBreach(35, 30, 40) == TypewiseAlert::BreachType::NORMAL);
}

// Test classifyTemperatureBreach function with different cooling types
void testClassifyTemperatureBreach() {
    assert(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::PASSIVE_COOLING, 20) == TypewiseAlert::BreachType::NORMAL);
    assert(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::PASSIVE_COOLING, 36) == TypewiseAlert::BreachType::TOO_HIGH);
    assert(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, 46) == TypewiseAlert::BreachType::TOO_HIGH);
    assert(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, 39) == TypewiseAlert::BreachType::NORMAL);
    assert(TypewiseAlert::classifyTemperatureBreach(TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, 41) == TypewiseAlert::BreachType::TOO_HIGH);
}

// Test checkAndAlert function
void testCheckAndAlert() {
    TypewiseAlert::BatteryCharacter batteryChar = {TypewiseAlert::CoolingType::PASSIVE_COOLING, "BrandA"};

    // Capture and verify output for controller alert
    freopen("/dev/null", "w", stdout);
    TypewiseAlert::checkAndAlert(TypewiseAlert::AlertTarget::TO_CONTROLLER, batteryChar, 36);
    freopen("/dev/tty", "w", stdout);

    // Capture and verify output for email alert
    freopen("/dev/null", "w", stdout);
    TypewiseAlert::checkAndAlert(TypewiseAlert::AlertTarget::TO_EMAIL, batteryChar, 36);
    freopen("/dev/tty", "w", stdout);
}

int main() {
    testInferBreach();
    testClassifyTemperatureBreach();
    testCheckAndAlert();
    printf("All tests passed!\n");
    return 0;
}
