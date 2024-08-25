#include "typewise-alert.h"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

// Implementations for CoolingStrategy
BreachType PassiveCooling::inferBreach(double temperature) const
{
    if (temperature < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (temperature > 35.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

BreachType HiActiveCooling::inferBreach(double temperature) const
{
    if (temperature < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (temperature > 45.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

BreachType MedActiveCooling::inferBreach(double temperature) const
{
    if (temperature < 0.0) 
    {
        return BreachType::TOO_LOW;
    }
    else if (temperature > 40.0) 
    {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL; 
}

// Implementations for CoolingContext
CoolingContext::CoolingContext(std::unique_ptr<CoolingStrategy> coolingStrategy)
    : strategy(std::move(coolingStrategy))
{
}
  
BreachType CoolingContext::inferBreach(double temperature) const
{
    return strategy->inferBreach(temperature);
}

// Implementations for AlertStrategy
void ControllerAlert::report(const BreachType breachType)
{
    const unsigned short alertHeader = 0xfeed;
    std::cout << std::hex << alertHeader << " : " << static_cast<std::uint16_t>(breachType) << std::endl;
}

void EmailAlert::report(const BreachType breachType)
{
    if (breachType != BreachType::NORMAL)
    {
        const std::string emailRecipient = "a.b@c.com";
        auto messageIt = breachMessages.find(breachType);
        if (messageIt != breachMessages.end())
        {
            std::cout << "To: " << emailRecipient << std::endl;
            std::cout << "Hi, " << messageIt->second << std::endl; 
        }
    }
}

// Implementations for Alerter
Alerter::Alerter(std::unique_ptr<AlertStrategy> alertStrategy)
    : strategy(std::move(alertStrategy))
{
}
  
void Alerter::report(const BreachType breachType)
{
    strategy->report(breachType);
}
