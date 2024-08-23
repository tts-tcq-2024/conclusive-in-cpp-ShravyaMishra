#include "battery-alert-system.h"
#include <iostream>

BatteryAlertSystem::BreachType BatteryAlertSystem::inferBreach(double temperature, double lowerLimit, double upperLimit) {
    if (temperature < lowerLimit) return BreachType::TOO_LOW;
    if (temperature > upperLimit) return BreachType::TOO_HIGH;
    return BreachType::NORMAL;
}

BatteryAlertSystem::BreachType BatteryAlertSystem::classifyTemperatureBreach(CoolingType coolingType, double temperature) {
    switch (coolingType) {
        case CoolingType::PASSIVE_COOLING:
            return inferBreach(temperature, 0, 35);
        case CoolingType::MED_ACTIVE_COOLING:
            return inferBreach(temperature, 0, 40);
        case CoolingType::HI_ACTIVE_COOLING:
            return inferBreach(temperature, 0, 45);
        default:
            return BreachType::NORMAL;
    }
}

void BatteryAlertSystem::checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperature) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperature);
    
    switch (alertTarget) {
        case AlertTarget::TO_CONTROLLER:
            std::cout << "feed : " << static_cast<int>(breachType) << "\n";
            break;
        case AlertTarget::TO_EMAIL:
            if (breachType == BreachType::TOO_HIGH) {
                std::cout << "To: a.b@c.com\nHi, the temperature is too high\n";
            }
            break;
    }
}
