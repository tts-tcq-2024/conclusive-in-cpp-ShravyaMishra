#include "typewise-alert.h"
#include <stdio.h>

// Initialize the static array of CoolingParameters inside the class
const TypewiseAlert::CoolingParameters* TypewiseAlert::getCoolingParameters() {
    static const CoolingParameters coolingParams[] = {
        {CoolingType::PASSIVE_COOLING, 0, 35},
        {CoolingType::HI_ACTIVE_COOLING, 0, 45},
        {CoolingType::MED_ACTIVE_COOLING, 0, 40},
    };
    return coolingParams;
}

TypewiseAlert::CoolingParameters TypewiseAlert::getParamsForCoolingType(CoolingType coolingType) {
    const CoolingParameters* params = getCoolingParameters();
    for (int i = 0; i < 3; ++i) {
        if (params[i].coolingType == coolingType) {
            return params[i];
        }
    }
    // Default case: return a default CoolingParameters structure
    return {CoolingType::PASSIVE_COOLING, 0, 35};  // Adjust the default values as needed
}

TypewiseAlert::BreachType TypewiseAlert::inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return BreachType::TOO_LOW;
    }
    if (value > upperLimit) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

TypewiseAlert::BreachType TypewiseAlert::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    CoolingParameters params = getParamsForCoolingType(coolingType);
    return inferBreach(temperatureInC, params.lowerLimit, params.upperLimit);
}

void TypewiseAlert::sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, static_cast<int>(breachType));
}

void TypewiseAlert::sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType != BreachType::NORMAL) {
        printf("To: %s\n", recipient);
        printf("Hi, the temperature is %s\n", breachType == BreachType::TOO_LOW ? "too low" : "too high");
    }
}

void TypewiseAlert::checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    if (alertTarget == AlertTarget::TO_CONTROLLER) {
        sendToController(breachType);
    } else {
        sendToEmail(breachType);
    }
}
