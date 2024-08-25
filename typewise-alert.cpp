#include "typewise-alert.h"
#include <cstdio> // for printf

// Initialize the static array of CoolingLimits inside the class
const TypewiseAlert::CoolingLimits* TypewiseAlert::retrieveCoolingLimits() {
    static const CoolingLimits coolingLimits[] = {
        {CoolingType::PASSIVE_COOLING, 0, 35},
        {CoolingType::HI_ACTIVE_COOLING, 0, 45},
        {CoolingType::MED_ACTIVE_COOLING, 0, 40},
    };
    return coolingLimits;
}

TypewiseAlert::CoolingLimits TypewiseAlert::findLimitsForCoolingType(CoolingType coolingType) {
    const CoolingLimits* limits = retrieveCoolingLimits();
    for (int index = 0; index < 3; ++index) {
        if (limits[index].coolingType == coolingType) {
            return limits[index];
        }
    }
    // Default case: return 0, 0 limits if cooling type is unknown
    return {coolingType, 0, 0};
}

TypewiseAlert::BreachType TypewiseAlert::evaluateBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return BreachType::TOO_LOW;
    }
    if (value > upperLimit) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

TypewiseAlert::BreachType TypewiseAlert::assessTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingLimits limits = findLimitsForCoolingType(coolingType);
    return evaluateBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void TypewiseAlert::alertController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, static_cast<int>(breachType));
}

void TypewiseAlert::alertEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType != BreachType::NORMAL) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature is %s\n", breachType == BreachType::TOO_LOW ? "too low" : "too high");
    }
}

void TypewiseAlert::checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
    BreachType breachType = assessTemperatureBreach(batteryChar.coolingType, temperatureInC);
    if (alertTarget == AlertTarget::TO_CONTROLLER) {
        alertController(breachType);
    } else {
        alertEmail(breachType);
    }
}
