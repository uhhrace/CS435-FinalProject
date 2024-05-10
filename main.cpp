/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>
#include <ratio>

InterruptIn reverseButton(PC_13);

bool motorDirection = true;
bool slowDownFlag = false;
bool speedUpFlag = false;

DigitalOut motorPos(PA_11);
DigitalOut motorNeg(PA_12);

PwmOut motorPWM(PC_9);

Ticker t;

void setMotorDirection(bool direction)
{
    if (motorDirection)
    {
        motorPos = 0;
        motorNeg = 1;
    }
    else
    {
        motorPos = 1;
        motorNeg = 0;
    }
}

void speedUp()
{
    if (speedUpFlag)
    {
        int speed = 1;

        while (speed < 1000)
        {
            motorPWM.pulsewidth_us(speed);
            speed += 2;
            printf("\nSpeeding up.");
            wait_us(100);
        }
        speedUpFlag = false;
    }
}

void slowDown()
{
    if (slowDownFlag)
    {
        int speed = 1000;

        while (speed > 0.0000001)
        {
            motorPWM.pulsewidth_us(speed);
            speed -= 2;
            printf("\nSlowing down.");
            wait_us(100);
        }
        slowDownFlag = false;
        // We're at 0, change direction and speed up again
        motorDirection = !motorDirection;
        speedUpFlag = true;
        // Stabilize, wait a second
        thread_sleep_for(1500);
    }
}

void buttonInterrupt()
{
    if (!slowDownFlag && !speedUpFlag)
    {
        // Start slowing down to switch directions
        slowDownFlag = true;
    }
}

/**
 * Main function
 * @brief Main function
 * @return int
 */
int main()
{
    // Wait for button interrupt to switch motor direction
    reverseButton.rise(buttonInterrupt);
    speedUpFlag = true;

    motorPWM = 1;
    motorPWM.period_us(1000);

    while (true)
    {
        if (slowDownFlag)
        {
            printf("Slowing down.");
            slowDown();
        }
        else if (speedUpFlag)
        {
            printf("Speeding up.");
            setMotorDirection(motorDirection);
            speedUp();
        }
        else
        {
            printf("\nMoving at speed.");
            setMotorDirection(motorDirection);
            thread_sleep_for(500);
        }
    }
}
