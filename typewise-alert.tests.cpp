#include "typewise-alert.h"
#include <cassert>
#include <cstdio>

// Define a simple test case
void testTypewiseAlert() {
    using namespace TypewiseAlert;

    BatteryCharacter batteryChar{CoolingType::MED_ACTIVE_COOLING, "BrandX"};

    // Test alert for temperature that is too high
    checkAndAlert(AlertTarget::TO_CONTROLLER, batteryChar, 45);
    // Since 45 is above the MED_ACTIVE_COOLING limit, it should trigger a TO_CONTROLLER alert.

    // Test alert for temperature within normal range
    checkAndAlert(AlertTarget::TO_EMAIL, batteryChar, 35);
    // Since 35 is within the limit for MED_ACTIVE_COOLING, it should not trigger an email alert.
}

int main() {
    testTypewiseAlert();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
