/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
// Stolen from https://os.mbed.com/teams/TVZ-Mechatronics-Team/wiki/Controlling-DC-motor
// TODO: Figure out where this lib comes from and how we can import it correctly
#include "HbridgeDCMotor.h"

DigitalIn reverseButton(BUTTON1);
PwmOut motorA(D7);
PwmOut motorB(D6);

// Motor direction is either CW or CCW
#define MOTOR_DIRECTION_CLOCKWISE = true;
#define MOTOR_DIRECTION_COUNTERCLOCKWISE = false;

boolean motorDirection = MOTOR_DIRECTION_CLOCKWISE;

void setMotorDirection(boolean direction)
{
    motorA = direction;
    motorB = direction;
}

void buttonInterrupt()
{
    boolean newDirection = !motorDirection;
    setMotorDirection(newDirection);
}

int main()
{

    // Wait for button interrupt to switch motor direction
    reverseButton.rise(&buttonInterrupt);

    // Sample time, switching frequency, ramp time, ramp time
    motorA.configure(10e-3, 25e3, 3, 3);
    motorB.configure(10e-3, 25e3, 3, 3);

    // Infinite loop forever
    while (true)
    {
        if (motorDirection == MOTOR_DIRECTION_CLOCKWISE)
        {
            motorA.setDutyCycle(0.5);
            motorB.setDutyCycle(0.5);
        }
        else
        {
            motorA.setDutyCycle(-0.5);
            motorB.setDutyCycle(-0.5);
        }
        thread_sleep_for(500);
    }
}
