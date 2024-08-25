#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <string>

class TypewiseAlert {
public:
    enum class CoolingType {
        PASSIVE_COOLING,
        HI_ACTIVE_COOLING,
        MED_ACTIVE_COOLING
    };

    enum class BreachType {
        NORMAL,
        TOO_LOW,
        TOO_HIGH
    };

    enum class AlertTarget {
        TO_CONTROLLER,
        TO_EMAIL
    };

    struct BatteryCharacter {
        CoolingType coolingType;
        std::string brand;
    };

    static BreachType assessTemperatureBreach(CoolingType coolingType, double temperatureInC);
    static void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);
    static BreachType evaluateBreach(double value, double lowerLimit, double upperLimit);

private:
    struct CoolingLimits {
        CoolingType coolingType;
        int lowerLimit;
        int upperLimit;
    };

    static CoolingLimits findLimitsForCoolingType(CoolingType coolingType);
    static const CoolingLimits* retrieveCoolingLimits();
    static void alertController(BreachType breachType);
    static void alertEmail(BreachType breachType);
};

#endif // TYPEWISE_ALERT_H
