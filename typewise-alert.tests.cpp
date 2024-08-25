#include "typewise-alert.h"
#include <gtest/gtest.h>
#include <sstream>

// Helper class to capture output for testing
class OutputCapture {
public:
    OutputCapture() {
        originalBuffer = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    }

    ~OutputCapture() {
        std::cout.rdbuf(originalBuffer);
    }

    std::string getCapturedOutput() {
        return buffer.str();
    }

private:
    std::streambuf* originalBuffer;
    std::stringstream buffer;
};

// Tests for CoolingContext and CoolingStrategy
TEST(CoolingContextTest, PassiveCoolingTest) {
    CoolingContext context(std::make_unique<PassiveCooling>());
    EXPECT_EQ(context.inferBreach(20.0), BreachType::NORMAL);
    EXPECT_EQ(context.inferBreach(36.0), BreachType::TOO_HIGH);
    EXPECT_EQ(context.inferBreach(-1.0), BreachType::TOO_LOW);
}

TEST(CoolingContextTest, HiActiveCoolingTest) {
    CoolingContext context(std::make_unique<HiActiveCooling>());
    EXPECT_EQ(context.inferBreach(20.0), BreachType::NORMAL);
    EXPECT_EQ(context.inferBreach(46.0), BreachType::TOO_HIGH);
    EXPECT_EQ(context.inferBreach(-1.0), BreachType::TOO_LOW);
}

TEST(CoolingContextTest, MedActiveCoolingTest) {
    CoolingContext context(std::make_unique<MedActiveCooling>());
    EXPECT_EQ(context.inferBreach(20.0), BreachType::NORMAL);
    EXPECT_EQ(context.inferBreach(41.0), BreachType::TOO_HIGH);
    EXPECT_EQ(context.inferBreach(-1.0), BreachType::TOO_LOW);
}

// Tests for ControllerAlert
TEST(AlertTest, ControllerAlertTest) {
    OutputCapture capture;
    ControllerAlert alert;
    alert.report(BreachType::TOO_
