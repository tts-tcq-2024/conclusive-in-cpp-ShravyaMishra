#include "typewise-alert.h"
#include <stdio.h>

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
    // Default to the first cooling type if not found (can adjust as needed)
    return params[0];
}

TypewiseAlert::BreachType TypewiseAlert::evaluateBreach(double temperature, double lowerLimit, double upperLimit) {
    if (temperature < lowerLimit) {
        return BreachType::TOO_LOW;
    }
    if (temperature > upperLimit) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

TypewiseAlert::BreachType TypewiseAlert::classifyTemperature(double temperatureInC, CoolingType coolingType) {
    CoolingParameters params = getParamsForCoolingType(coolingType);
    return evaluateBreach(temperatureInC, params.lowerLimit, params.upperLimit);
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

void TypewiseAlert::monitorAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperature(temperatureInC, batteryChar.coolingType);
    if (alertTarget == AlertTarget::TO_CONTROLLER) {
        sendToController(breachType);
    } else {
        sendToEmail(breachType);
    }
}
