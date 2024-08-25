#include "typewise-alert.h"
#include <stdio.h>

BreachType PassiveCooling::inferBreach(double value) const
{
    if (value < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (value > 35.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

BreachType HiActiveCooling::inferBreach(double value) const
{
    if (value < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (value > 45.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

BreachType MedActiveCooling::inferBreach(double value) const
{
    if (value < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (value > 40.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

CoolingContext::CoolingContext(std::unique_ptr<CoolingStrategy> strategy) : strategy(std::move(strategy))
{
}
  
BreachType CoolingContext::inferBreach(double value) const
{
  return strategy->inferBreach(value);
}

void ControllerAlert::report(const BreachType breachType)
{
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<std::uint16_t>(breachType) << std::endl;
}

void EmailAlert::report(const BreachType breachType)
{
    if(breachType != BreachType::NORMAL)
    {
        const std::string recepient = "a.b@c.com";
        auto it = breachMessages.find(breachType);
        if(it != breachMessages.end())
        {
            std::cout << "To: " << recepient << std::endl;
            std::cout << "Hi, " << it->second << std::endl; 
        }
    }
}

Alerter::Alerter(std::unique_ptr<AlertStrategy> strategy) : strategy(std::move(strategy))
{
}
  
void Alerter::report(const BreachType breachType)
{
  strategy->report(breachType);
}
