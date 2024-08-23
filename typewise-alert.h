#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <string>

enum CoolingMode {
    PASSIVE,
    HIGH_ACTIVE,
    MEDIUM_ACTIVE
};

enum AlertType {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
};

enum NotificationTarget {
    CONTROLLER,
    EMAIL
};

struct BatteryInfo {
    CoolingMode mode;
    std::string brand;
};

AlertType evaluateBreach(double temperature, double lowerLimit, double upperLimit);

AlertType categorizeTemperature(CoolingMode mode, double temperature);

void triggerAlert(NotificationTarget target, BatteryInfo batteryInfo, double temperature);

void notifyController(AlertType alert);

void notifyEmail(AlertType alert);

#endif
