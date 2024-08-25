#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

typedef enum {
    PASSIVE_COOLING,
    MED_ACTIVE_COOLING,
    HI_ACTIVE_COOLING
} CoolingType;

typedef enum {
    TOO_LOW,
    TOO_HIGH,
    NORMAL
} BreachType;

typedef enum {
    TO_CONTROLLER,
    TO_EMAIL
} AlertTarget;

typedef struct {
    CoolingType coolingType;
} BatteryCharacter;

// Function prototypes
BreachType inferBreach(float temperatureInCelsius, float lowerLimit, float upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, float temperatureInCelsius);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, float temperatureInCelsius);

#endif // TYPEWISE_ALERT_H
