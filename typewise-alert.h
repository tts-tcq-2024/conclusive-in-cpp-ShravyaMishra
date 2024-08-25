#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

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
    char brand[48];
};

class TypewiseAlert {
public:
    struct CoolingParameters {
        CoolingType coolingType;
        double lowerLimit;
        double upperLimit;
    };
    
    static const CoolingParameters* getCoolingParameters();
    static CoolingParameters getParamsForCoolingType(CoolingType coolingType);
    static BreachType evaluateBreach(double temperature, double lowerLimit, double upperLimit);
    static BreachType classifyTemperature(double temperatureInC, CoolingType coolingType);
    static void sendToController(BreachType breachType);
    static void sendToEmail(BreachType breachType);
    static void monitorAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);
};

#endif // TYPEWISE_ALERT_H
