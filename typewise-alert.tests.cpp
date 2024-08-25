#include "typewise-alert.h"

// Implementations for CoolingStrategy
BreachType PassiveCooling::inferBreach(double value) const {
    if (value < 0.0) {
        return BreachType::TOO_LOW;
    } else if (value > 35.0) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

BreachType HiActiveCooling::inferBreach(double value) const {
    if (value < 0.0) {
        return BreachType::TOO_LOW;
    } else if (value > 45.0) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

BreachType MedActiveCooling::inferBreach(double value) const {
    if (value < 0.0) {
        return BreachType::TOO_LOW;
    } else if (value > 40.0) {
        return BreachType::TOO_HIGH;
    }
    return BreachType::NORMAL;
}

// Implementations for CoolingContext
CoolingContext::CoolingContext(std::unique_ptr<CoolingStrategy> strategy)
    : strategy(std::move(strategy)) {}

BreachType CoolingContext::inferBreach(double value) const {
    return strategy->inferBreach(value);
}

// Implementations for AlertStrategy
void ControllerAlert::report(BreachType breachType) {
    const unsigned short header = 0xfeed;
    std::cout << std::hex << header << " : " << static_cast<std::uint16_t>(breachType) << std::endl;
}

void EmailAlert::report(BreachType breachType) {
    if (breachType != BreachType::NORMAL) {
        const std::string recepient = "a.b@c.com";
        auto it = breachMessages.find(breachType);
        if (it != breachMessages.end()) {
            std::cout << "To: " << recepient << std::endl;
            std::cout << "Hi, " << it->second << std::endl;
        }
    }
}

// Implementations for Alerter
Alerter::Alerter(std::unique_ptr<AlertStrategy> strategy)
    : strategy(std::move(strategy)) {}

void Alerter::report(BreachType breachType) {
    strategy->report(breachType);
}
