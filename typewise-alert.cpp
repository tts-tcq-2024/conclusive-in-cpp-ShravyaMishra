#include "typewise-alert.h"
#include <iostream>

// Define the cooling limits for different cooling types
const TypewiseAlert::CoolingLimits coolingLimits[] = {
    { TypewiseAlert::CoolingType::PASSIVE_COOLING, 0, 35 },
    { TypewiseAlert::CoolingType::MED_ACTIVE_COOLING, 0, 40 },
    { TypewiseAlert::CoolingType::HI_ACTIVE_COOLING, 0, 45 }
};

// Return the cooling limits for a given cooling type
const TypewiseAlert::CoolingLimits* TypewiseAlert::getCoolingLimits() {
    return coolingLimits;
}

// Infer the breach type based on the temperature value and limits
TypewiseAlert::BreachType TypewiseAlert::inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return BreachType::TOO_LOW;
    if (value > upperLimit) return BreachType::TOO_HIGH;
    return BreachType::NORMAL;
}

// Get the cooling limits for a specific cooling type
TypewiseAlert::CoolingLimits TypewiseAlert::getLimitsForCoolingType(CoolingType coolingType) {
    const CoolingLimits* limits = getCoolingLimits();
    for (int i = 0; i < sizeof(coolingLimits) / sizeof(coolingLimits[0]); ++i) {
        if (limits[i].coolingType == coolingType) {
            return limits[i];
        }
    }
    // Default limits in case of an unknown cooling type
    return { coolingType, 0, 0 };
}

// Classify the temperature breach based on the cooling type and temperature
TypewiseAlert::BreachType TypewiseAlert::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingLimits limits = getLimitsForCoolingType(coolingType);
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

// Send alert to the controller based on the breach type
void TypewiseAlert::sendToController(BreachType breachType) {
    std::cout << "feed : " << static_cast<int>(breachType) << "\n";
}

// Send alert to email based on the breach type
void TypewiseAlert::sendToEmail(BreachType breachType) {
    if (breachType == BreachType::TOO_HIGH) {
        std::cout << "To: a.b@c.com\nHi, the temperature is too high\n";
    }
}

// Check and send alert based on the target, battery character, and temperature
void TypewiseAlert::checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    switch (alertTarget) {
        case AlertTarget::TO_CONTROLLER:
            sendToController(breachType);
            break;
        case AlertTarget::TO_EMAIL:
            sendToEmail(breachType);
            break;
    }
}
