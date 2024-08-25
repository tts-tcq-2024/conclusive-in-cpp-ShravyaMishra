#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, PassiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<PassiveCooling>());
    EXPECT_EQ(coolingContext->inferBreach(-1.0), BreachType::TOO_LOW);
    EXPECT_EQ(coolingContext->inferBreach(36.0), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingContext->inferBreach(30.0), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, HiActiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<HiActiveCooling>());
    EXPECT_EQ(coolingContext->inferBreach(-1.0), BreachType::TOO_LOW);
    EXPECT_EQ(coolingContext->inferBreach(46.0), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingContext->inferBreach(30.0), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, MediumActiveCoolingBreach) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    EXPECT_EQ(coolingContext->inferBreach(-1.0), BreachType::TOO_LOW);
    EXPECT_EQ(coolingContext->inferBreach(41.0), BreachType::TOO_HIGH);
    EXPECT_EQ(coolingContext->inferBreach(40.0), BreachType::NORMAL);
}

TEST(TypeWiseAlertTestSuite, ControllerAlert) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    BreachType breachType = coolingContext->inferBreach(-1.0);
    EXPECT_EQ(breachType, BreachType::TOO_LOW);
    
    OutputCapture capture; // Capture output for testing
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<ControllerAlert>());
    alerter->report(breachType);
    
    std::string output = capture.getCapturedOutput();
    EXPECT_NE(output.find("feed"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos); // 1 corresponds to TOO_LOW
}

TEST(TypeWiseAlertTestSuite, EmailAlertForHigh) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<MedActiveCooling>());
    BreachType breachType = coolingContext->inferBreach(41.0);
    EXPECT_EQ(breachType, BreachType::TOO_HIGH);
    
    OutputCapture capture; // Capture output for testing
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<EmailAlert>());
    alerter->report(breachType);
    
    std::string output = capture.getCapturedOutput();
    EXPECT_NE(output.find("To: a.b@c.com"), std::string::npos);
    EXPECT_NE(output.find("Hi, Temperature is too high"), std::string::npos);
}

TEST(TypeWiseAlertTestSuite, NoEmailAlertForNormal) 
{
    std::unique_ptr<CoolingContext> coolingContext = std::make_unique<CoolingContext>(std::make_unique<PassiveCooling>());
    BreachType breachType = coolingContext->inferBreach(30.0);
    EXPECT_EQ(breachType, BreachType::NORMAL);
    
    OutputCapture capture; // Capture output for testing
    std::unique_ptr<Alerter> alerter = std::make_unique<Alerter>(std::make_unique<EmailAlert>());
    alerter->report(breachType);
    
    std::string output = capture.getCapturedOutput();
    EXPECT_EQ(output, ""); // No output should be generated for NORMAL
}
