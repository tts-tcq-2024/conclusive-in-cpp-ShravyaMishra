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

    struct CoolingParameters {
        CoolingType coolingType;
        double lowerLimit;
        double upperLimit;
    };

    static BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
    static void checkAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);

private:
    static BreachType inferBreach(double value, double lowerLimit, double upperLimit);
    static const CoolingParameters* getCoolingParameters();
    static CoolingParameters getParamsForCoolingType(CoolingType coolingType);
    static void sendToController(BreachType breachType);
    static void sendToEmail(BreachType breachType);
};

#endif // TYPEWISE_ALERT_H
