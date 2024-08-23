#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

typedef enum {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
} BreachType;

typedef enum {
    TO_CONTROLLER,
    TO_EMAIL
} AlertTarget;

typedef struct {
    CoolingType coolingType;
} BatteryCharacter;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperature);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperature);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

#endif
