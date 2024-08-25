#include "typewise-alert.h"
#include <stdio.h>

// Function to infer if temperature is too low, too high, or normal
BreachType inferBreach(float temperatureInCelsius, float lowerLimit, float upperLimit) {
    if (temperatureInCelsius < lowerLimit) {
        return TOO_LOW;
    } else if (temperatureInCelsius > upperLimit) {
        return TOO_HIGH;
    } else {
        return NORMAL;
    }
}

// Function to classify temperature breach based on cooling type
BreachType classifyTemperatureBreach(CoolingType coolingType, float temperatureInCelsius) {
    float lowerLimit, upperLimit;

    switch (coolingType) {
        case PASSIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 35;
            break;
        case MED_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 40;
            break;
        case HI_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 45;
            break;
        default:
            return NORMAL; // Default case if cooling type is unknown
    }

    return inferBreach(temperatureInCelsius, lowerLimit, upperLimit);
}

// Function to send alert based on the breach type and target
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, float temperatureInCelsius) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInCelsius);

    switch (alertTarget) {
        case TO_CONTROLLER:
            // Send alert to controller (for now, just print to stdout)
            printf("Alert to controller: BreachType %d\n", breachType);
            break;
        case TO_EMAIL:
            // Send alert via email (for now, just print to stdout)
            printf("Alert via email: BreachType %d\n", breachType);
            break;
        default:
            break; // Handle unknown alert targets
    }
}
