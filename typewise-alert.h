#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <memory>
#include <unordered_map>
#include <iostream>
#include <string>

// Define enum for breach types
enum class BreachType {
    TOO_LOW,
    TOO_HIGH,
    NORMAL
};

// Define enum for cooling types
enum class CoolingType {
    PASSIVE_COOLING,
    MED_ACTIVE_COOLING,
    HI_ACTIVE_COOLING
};

// Abstract class for Cooling Strategy
class CoolingStrategy {
public:
    virtual ~CoolingStrategy() = default;
    virtual BreachType inferBreach(double value) const = 0;
};

// Concrete classes for different cooling strategies
class PassiveCooling : public CoolingStrategy {
public:
    BreachType inferBreach(double value) const override;
};

class HiActiveCooling : public CoolingStrategy {
public:
    BreachType inferBreach(double value) const override;
};

class MedActiveCooling : public CoolingStrategy {
public:
    BreachType inferBreach(double value) const override;
};

// Context class that uses a CoolingStrategy
class CoolingContext {
public:
    CoolingContext(std::unique_ptr<CoolingStrategy> strategy);
    BreachType inferBreach(double value) const;
private:
    std::unique_ptr<CoolingStrategy> strategy;
};

// Abstract class for Alert Strategy
class AlertStrategy {
public:
    virtual ~AlertStrategy() = default;
    virtual void report(BreachType breachType) = 0;
};

// Concrete classes for different alert strategies
class ControllerAlert : public AlertStrategy {
public:
    void report(BreachType breachType) override;
};

class EmailAlert : public AlertStrategy {
public:
    void report(BreachType breachType) override;
private:
    const std::unordered_map<BreachType, std::string> breachMessages = {
        {BreachType::TOO_LOW, "Temperature is too low"},
        {BreachType::TOO_HIGH, "Temperature is too high"}
    };
};

// Alerter class that uses an AlertStrategy
class Alerter {
public:
    Alerter(std::unique_ptr<AlertStrategy> strategy);
    void report(BreachType breachType);
private:
    std::unique_ptr<AlertStrategy> strategy;
};

#endif // TYPEWISE_ALERT_H
