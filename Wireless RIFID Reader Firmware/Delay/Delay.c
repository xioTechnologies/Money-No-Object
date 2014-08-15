/*
 * File:   Delay.c
 * Author: Seb Madgwick
 *
 * Uses core timer. Other modules may use the core timer without affecting the
 * delay provided that the core timer is not written due until the delay
 * function has completed.
 *
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "SystemClock.h"

//------------------------------------------------------------------------------
// Functions

void DelayMs(unsigned int milliseconds) {
    unsigned int t = ReadCoreTimer();
    while ((ReadCoreTimer() - t) < (milliseconds * ((SYSCLK / 2) / 1000)));
}

void DelayUs(unsigned int microseconds) {
    unsigned int t = ReadCoreTimer();
    while ((ReadCoreTimer() - t) < (microseconds * ((SYSCLK / 2) / 1000000)));
}

//------------------------------------------------------------------------------
// End of file
