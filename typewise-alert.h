#pragma once

#include <string>

class TypewiseAlert {
public:
    enum class BreachType {
        NORMAL,
        TOO_LOW,
        TOO_HIGH
    };

    enum class CoolingType {
        PASSIVE_COOLING,
        HI_ACTIVE_COOLING,
        MED_ACTIVE_COOLING
    };

    enum class AlertTarget {
        TO_CONTROLLER,
        TO_EMAIL
    };

    struct BatteryCharacter {
        CoolingType coolingType;
        std::string brand;
    };

    static BreachType evaluateBreach(double temperature, double lowerLimit, double upperLimit);
    static BreachType classifyTemperature(double temperatureInC, CoolingType coolingType);
    static void sendToController(BreachType breachType);
    static void sendToEmail(BreachType breachType);
    static void monitorAndAlert(AlertTarget alertTarget, const BatteryCharacter& batteryChar, double temperatureInC);

private:
    struct CoolingParameters {
        CoolingType coolingType;
        double lowerLimit;
        double upperLimit;
    };

    static const CoolingParameters* getCoolingParameters();
    static CoolingParameters getParamsForCoolingType(CoolingType coolingType);
};
