#include <iostream>

void testSetMotorDirection()
{
    // Test case 1: Motor direction is clockwise
    setMotorDirection(true);
    // Verify that motorA and motorB have the correct duty cycle for clockwise direction
    if (motorA.getDutyCycle() == MOTOR_DUTY_CYCLE_CLOCKWISE && motorB.getDutyCycle() == MOTOR_DUTY_CYCLE_CLOCKWISE)
    {
        std::cout << "Test case 1 passed: Motor direction is set to clockwise.\n";
    }
    else
    {
        std::cout << "Test case 1 failed: Motor direction is not set to clockwise.\n";
    }

    // Test case 2: Motor direction is counterclockwise
    setMotorDirection(false);
    // Verify that motorA and motorB have the correct duty cycle for counterclockwise direction
    if (motorA.getDutyCycle() == MOTOR_DUTY_CYCLE_COUNTERCLOCKWISE && motorB.getDutyCycle() == MOTOR_DUTY_CYCLE_COUNTERCLOCKWISE)
    {
        std::cout << "Test case 2 passed: Motor direction is set to counterclockwise.\n";
    }
    else
    {
        std::cout << "Test case 2 failed: Motor direction is not set to counterclockwise.\n";
    }
}

void testButtonInterrupt()
{
    // Test case 1: Button interrupt changes motor direction
    motorDirection = true; // Set initial motor direction to clockwise
    buttonInterrupt();     // Simulate button interrupt
    if (motorDirection == false)
    {
        std::cout << "Test case 1 passed: Button interrupt changed motor direction to counterclockwise.\n";
    }
    else
    {
        std::cout << "Test case 1 failed: Button interrupt did not change motor direction.\n";
    }

    // Test case 2: Button interrupt changes motor direction back to original
    motorDirection = false; // Set initial motor direction to counterclockwise
    buttonInterrupt();      // Simulate button interrupt
    if (motorDirection == true)
    {
        std::cout << "Test case 2 passed: Button interrupt changed motor direction back to clockwise.\n";
    }
    else
    {
        std::cout << "Test case 2 failed: Button interrupt did not change motor direction back to original.\n";
    }
}

void testSpeedUp()
{
    // Test case 1: Speed up from 1 to 1000
    speedUpFlag = true;
    speedUp();
    if (motorPWM.getPulsewidth_us() == 1000)
    {
        std::cout << "Test case 1 passed: Motor speed increased to 1000.\n";
    }
    else
    {
        std::cout << "Test case 1 failed: Motor speed did not increase to 1000.\n";
    }

    // Test case 2: Speed up from 1000 to 1000 (no change)
    speedUpFlag = true;
    speedUp();
    if (motorPWM.getPulsewidth_us() == 1000)
    {
        std::cout << "Test case 2 passed: Motor speed remained at 1000.\n";
    }
    else
    {
        std::cout << "Test case 2 failed: Motor speed did not remain at 1000.\n";
    }
}

void testSlowDown()
{
    // Test case 1: Slow down from 1000 to 0
    slowDownFlag = true;
    slowDown();
    if (motorPWM.getPulsewidth_us() == 0)
    {
        std::cout << "Test case 1 passed: Motor speed decreased to 0.\n";
    }
    else
    {
        std::cout << "Test case 1 failed: Motor speed did not decrease to 0.\n";
    }

    // Test case 2: Slow down from 0 to 0 (no change)
    slowDownFlag = true;
    slowDown();
    if (motorPWM.getPulsewidth_us() == 0)
    {
        std::cout << "Test case 2 passed: Motor speed remained at 0.\n";
    }
    else
    {
        std::cout << "Test case 2 failed: Motor speed did not remain at 0.\n";
    }
}

void testMain()
{
    // Test case 1: Motor direction is set to clockwise
    motorDirection = true;
    slowDownFlag = false;
    speedUpFlag = false;
    main();
    // Verify that motor direction is set to clockwise
    if (motorPos == 0 && motorNeg == 1)
    {
        std::cout << "Test case 1 passed: Motor direction is set to clockwise.\n";
    }
    else
    {
        std::cout << "Test case 1 failed: Motor direction is not set to clockwise.\n";
    }

    // Test case 2: Motor direction is set to counterclockwise
    motorDirection = false;
    slowDownFlag = false;
    speedUpFlag = false;
    main();
    // Verify that motor direction is set to counterclockwise
    if (motorPos == 1 && motorNeg == 0)
    {
        std::cout << "Test case 2 passed: Motor direction is set to counterclockwise.\n";
    }
    else
    {
        std::cout << "Test case 2 failed: Motor direction is not set to counterclockwise.\n";
    }

    // Test case 3: Motor speed is increased
    motorDirection = true;
    slowDownFlag = false;
    speedUpFlag = true;
    main();
    // Verify that motor speed is increased to 1000
    if (motorPWM.getPulsewidth_us() == 1000)
    {
        std::cout << "Test case 3 passed: Motor speed is increased to 1000.\n";
    }
    else
    {
        std::cout << "Test case 3 failed: Motor speed is not increased to 1000.\n";
    }

    // Test case 4: Motor speed is decreased
    motorDirection = true;
    slowDownFlag = true;
    speedUpFlag = false;
    main();
    // Verify that motor speed is decreased to 0
    if (motorPWM.getPulsewidth_us() == 0)
    {
        std::cout << "Test case 4 passed: Motor speed is decreased to 0.\n";
    }
    else
    {
        std::cout << "Test case 4 failed: Motor speed is not decreased to 0.\n";
    }
}

int main()
{
    testSetMotorDirection();
    testButtonInterrupt();
    testSpeedUp();
    testSlowDown();
    testMain();

    return 0;
}