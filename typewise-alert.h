#pragma once
#include <memory>
#include <map>
#include "BreachType.h"

class CoolingStrategy
{
    public:
    virtual ~CoolingStrategy()= default;
    virtual BreachType inferBreach(double value) const = 0;
};

class PassiveCooling : public CoolingStrategy
{
    public:
    BreachType inferBreach(double value) const override;
};

class HiActiveCooling : public CoolingStrategy
{
    public:
    BreachType inferBreach(double value) const override;
};

class MedActiveCooling : public CoolingStrategy
{
    public:
    BreachType inferBreach(double value) const override;
};

class CoolingContext 
{
  private:
  std::unique_ptr<CoolingStrategy> strategy;
  
  public:
  CoolingContext(std::unique_ptr<CoolingStrategy> strategy);
  BreachType inferBreach(double value) const;  
};

class AlertStrategy 
{
public:
    virtual ~AlertStrategy() = default;
    virtual void report(const BreachType breachType) = 0;
};

class ControllerAlert : public AlertStrategy 
{
public:
    void report(const BreachType breachType) override;
};

class EmailAlert : public AlertStrategy 
{
public:
    void report(const BreachType breachType) override;
private:
    const std::map<const BreachType, std::string> breachMessages =
    {
        {BreachType::TOO_LOW, "the temperature is too low"},
        {BreachType::TOO_HIGH, "the temperature is too high"},
    };
};

class Alerter
{
  private:
      std::unique_ptr<AlertStrategy> strategy;
  public:
      Alerter(std::unique_ptr<AlertStrategy> strategy);
      void report(const BreachType breachType);
};
