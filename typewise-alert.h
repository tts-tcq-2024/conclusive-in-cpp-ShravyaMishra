#ifndef BATTERY_ALERT_SYSTEM_H
#define BATTERY_ALERT_SYSTEM_H

#include <string>

class BatteryAlertSystem {
public:
    enum class CoolingType {
        PASSIVE_COOLING,
        MED_ACTIVE_COOLING,
        HI_ACTIVE_COOLING
    };

    enum class AlertTarget {
        TO_CONTROLLER,
        TO_EMAIL
    };

    enum class BreachType {
        NORMAL,
        TOO_LOW,
        TOO_HIGH
    };

    struct BatteryCharacter {
        CoolingType coolingType;
        std::string brand;
    };

    static BreachType inferBreach(double temperature, double lowerLimit, double upperLimit);
    static BreachType classifyTemperatureBreach(CoolingType coolingType, double temperature);
    static void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperature);
};

#endif // BATTERY_ALERT_SYSTEM_H
