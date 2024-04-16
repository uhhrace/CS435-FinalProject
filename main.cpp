/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
// Library from https://os.mbed.com/teams/TVZ-Mechatronics-Team/wiki/Controlling-DC-motor
#include "HBridgeDCMotor.h"


// Motor direction is either CW or CCW
#define MOTOR_DIRECTION_CLOCKWISE true;
#define MOTOR_DIRECTION_COUNTERCLOCKWISE false;

const PinName MOTOR_A_GROUND_PIN(D6);
const PinName MOTOR_B_GROUND_PIN(D7);
const PinName MOTOR_A_POWER_PIN(D8);
const PinName MOTOR_B_POWER_PIN(D9);

DigitalIn reverseButton(BUTTON1);

HBridgeDCMotor motorA(MOTOR_A_GROUND_PIN, MOTOR_A_POWER_PIN);
HBridgeDCMotor motorB(MOTOR_B_GROUND_PIN, MOTOR_B_POWER_PIN);

bool motorDirection = MOTOR_DIRECTION_CLOCKWISE;

void setMotorDirection(bool direction)
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
}

void buttonInterrupt()
{
    motorDirection = !motorDirection;
    // setMotorDirection(newDirection);
}

int main()
{
    // Wait for button interrupt to switch motor direction
    reverseButton.rise(&buttonInterrupt);

    // Sample time, switching frequency, ramp time, ramp time
    motorA.configure(10e-3, 25e3, 3, 3);
    motorB.configure(10e-3, 25e3, 3, 3);

    while (true)
    {
        setMotorDirection(motorDirection);
        thread_sleep_for(500);
    }
}
