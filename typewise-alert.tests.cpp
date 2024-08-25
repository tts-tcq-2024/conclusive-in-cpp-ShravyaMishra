#include "typewise-alert.h"
#include <cassert>

void testTemperatureClassification() {
    assert(TypewiseAlert::classifyTemperature(20, CoolingType::PASSIVE_COOLING) == BreachType::NORMAL);
    assert(TypewiseAlert::classifyTemperature(50, CoolingType::HI_ACTIVE_COOLING) == BreachType::TOO_HIGH);
    assert(TypewiseAlert::classifyTemperature(-5, CoolingType::MED_ACTIVE_COOLING) == BreachType::TOO_LOW);
}

void testAlertingMechanism() {
    BatteryCharacter batteryChar = {CoolingType::HI_ACTIVE_COOLING, "BrandA"};
    
    TypewiseAlert::monitorAndAlert(AlertTarget::TO_CONTROLLER, batteryChar, 30);
    TypewiseAlert::monitorAndAlert(AlertTarget::TO_EMAIL, batteryChar, 50);
}

int main() {
    testTemperatureClassification();
    testAlertingMechanism();
    
    printf("All tests passed!\n");
    return 0;
}
