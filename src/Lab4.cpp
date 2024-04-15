/*----------------------------------------------------------------------------
LAB EXERCISE 4 -PART 2 - TICKER AND PWM
 ----------------------------------------
Make an audio player to play a music

Output: PWM Speaker (play the music)

GOOD LUCK!

*----------------------------------------------------------------------------*/

#include "mbed.h"

// Define the frequency of basic music notes
#define Do 0.5
#define Re 0.45
#define Mi 0.4
#define Fa 0.36
#define So 0.33
#define La 0.31
#define Si 0.3
#define No 0

// Define the beat length (e.g. whole note, half note)
#define b1 0.5
#define b2 0.25
#define b3 0.125
#define b4 0.0625

// Define the musical piece
float note[] = {Mi, No, Mi, No, Mi, No, Mi, No, Mi, No, Mi, No, Mi, No, So, No, Do, No, Re, No, Mi, No, Fa, No, Fa, No, Fa, No, Fa, No, Fa, No, Mi, No, Mi, No, Mi, No, Mi, No, Mi, Re, No, Re, Mi, Re, No, So, No};
float beat[] = {b3, b3, b3, b3, b2, b2, b3, b3, b3, b3, b2, b2, b3, b3, b3, b3, b3, b3, b3, b3, b2, b1, b3, b3, b3, b3, b3, b3, b3, b3, b3, b3, b3, b3, b3, b3, b4, b4, b4, b4, b2, b3, b3, b2, b2, b2, b2, b2, b2};

// Define the PWM output for the speaker
PwmOut buzzer(D9);

// Define the time ticker
Ticker ticker;

// Static variable to iterate through note and beat arrays
static int k;

/*----------------------------------------------------------------------------
 Interrupt Service Routine
 *----------------------------------------------------------------------------*/
// Define the ticker ISR
void timer_ISR()
{
    /*
    The time ticker ISR will be periodically triggered after every single note.
        To do that:
        -  Update the PWM frequency to that of kth music note
        -  increment k to consider the next music note
        -  reconfigure the tick interrupt time based on the beat length of kth music note
    */
    buzzer.period(1.0 / note[k]);       // set the frequency of the buzzer
    k++;                                // increment k to consider the next music note
    ticker.attach(&timer_ISR, beat[k]); // reconfigure the tick interrupt time based on the beat length of kth music note
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main()
{

    k = 0; // start by considering the first music note

    // Initialize volume to 0.2
    buzzer = 0.2;

    // Initialize ticker to call timer_ISR after 0.1 seconds
    buzzer.attach(&timer_ISR, 0.1);

    // sleep and wait for recurring interrupts
    while (1)
    {
        if (k == sizeof(note))
        {
            k = 0;
        }
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2019*************************************