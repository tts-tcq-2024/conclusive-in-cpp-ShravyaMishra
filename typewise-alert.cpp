#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double temperature, double lowerThreshold, double upperThreshold) {
    if (temperature < lowerThreshold) {
        return TOO_LOW;
    }
    if (temperature > upperThreshold) {
        return TOO_HIGH;
    }
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperature) {
    double upperThreshold = 0;
    
    if (coolingType == PASSIVE_COOLING) {
        upperThreshold = 35;
    } else if (coolingType == MED_ACTIVE_COOLING) {
        upperThreshold = 40;
    } else if (coolingType == HI_ACTIVE_COOLING) {
        upperThreshold = 45;
    }

    return inferBreach(temperature, 0, upperThreshold);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperature) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperature);

    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void sendToController(BreachType breachType) {
    printf("0xfeed : %d\n", breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\nHi, the temperature is too low\n", recipient);
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\nHi, the temperature is too high\n", recipient);
    } else {
        printf("To: %s\nHi, the temperature is normal\n", recipient);
    }
}
