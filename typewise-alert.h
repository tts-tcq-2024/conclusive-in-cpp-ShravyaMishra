#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

enum class CoolingType { PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING };
enum class BreachType { NORMAL, TOO_LOW, TOO_HIGH };
enum class AlertTarget { TO_CONTROLLER, TO_EMAIL };

struct BatteryCharacter {
    CoolingType coolingType;
    const char* brand;
};

class TypewiseAlert {
public:
    static BreachType classifyTemperature(double temperatureInC, CoolingType coolingType);
    static void monitorAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);

private:
    struct CoolingParameters {
        CoolingType coolingType;
        double lowerLimit;
        double upperLimit;
    };

    static const CoolingParameters* getCoolingParameters();
    static CoolingParameters getParamsForCoolingType(CoolingType coolingType);
    static BreachType evaluateBreach(double temperature, double lowerLimit, double upperLimit);
    static void sendToController(BreachType breachType);
    static void sendToEmail(BreachType breachType);
};

#endif // TYPEWISE_ALERT_H
