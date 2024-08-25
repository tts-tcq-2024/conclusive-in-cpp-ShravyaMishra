#include "typewise-alert.h"
#include <cassert>
#include <cstdio>

// Function to test temperature classification
void testTemperatureClassification() {
    assert(TypewiseAlert::classifyTemperature(20, CoolingType::PASSIVE_COOLING) == BreachType::NORMAL);
    assert(TypewiseAlert::classifyTemperature(50, CoolingType::HI_ACTIVE_COOLING) == BreachType::TOO_HIGH);
    assert(TypewiseAlert::classifyTemperature(-5, CoolingType::MED_ACTIVE_COOLING) == BreachType::TOO_LOW);
}

// Function to test the alert mechanism
void testTypewiseAlert() {
    BatteryCharacter batteryChar{CoolingType::MED_ACTIVE_COOLING, "BrandX"};

    // Test alert for temperature that is too high
    TypewiseAlert::monitorAndAlert(AlertTarget::TO_CONTROLLER, batteryChar, 45);
    // Since 45 is above the MED_ACTIVE_COOLING limit, it should trigger a TO_CONTROLLER alert.

    // Test alert for temperature within the normal range
    TypewiseAlert::monitorAndAlert(AlertTarget::TO_EMAIL, batteryChar, 35);
    // Since 35 is within the MED_ACTIVE_COOLING limit, it should not trigger an alert.
}

int main() {
    // Run both tests
    testTemperatureClassification();
    testTypewiseAlert();

    printf("All tests passed!\n");
    return 0;
}
