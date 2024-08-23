#include "typewise-alert.h"
#include <iostream>

AlertType evaluateBreach(double temperature, double lowerLimit, double upperLimit) {
    if (temperature < lowerLimit) {
        return TOO_LOW;
    }
    if (temperature > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

double getLowerLimit(CoolingMode mode) {
    return 0; // All modes have the same lower limit
}

double getUpperLimit(CoolingMode mode) {
    switch (mode) {
        case PASSIVE:
            return 35;
        case HIGH_ACTIVE:
            return 45;
        case MEDIUM_ACTIVE:
            return 40;
        default:
            return 0; // Default case for safety
    }
}

AlertType categorizeTemperature(CoolingMode mode, double temperature) {
    double lowerLimit = getLowerLimit(mode);
    double upperLimit = getUpperLimit(mode);
    return evaluateBreach(temperature, lowerLimit, upperLimit);
}

void triggerAlert(NotificationTarget target, BatteryInfo batteryInfo, double temperature) {
    AlertType alert = categorizeTemperature(batteryInfo.mode, temperature);
    if (target == CONTROLLER) {
        notifyController(alert);
    } else if (target == EMAIL) {
        notifyEmail(alert);
    }
}

void notifyController(AlertType alert) {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << alert << std::endl;
}

void notifyEmail(AlertType alert) {
    const std::string recipient = "a.b@c.com";
    std::cout << "To: " << recipient << std::endl;
    if (alert == TOO_LOW) {
        std::cout << "Hi, the temperature is too low" << std::endl;
    } else if (alert == TOO_HIGH) {
        std::cout << "Hi, the temperature is too high" << std::endl;
    } else {
        std::cout << "Hi, the temperature is normal" << std::endl;
    }
}
