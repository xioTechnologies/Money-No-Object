/*
 * File:   SystemClock.h
 * Author: Seb Madgwick
 */

#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

//------------------------------------------------------------------------------
// Definitions

#define SYSCLK 80000000ul
#define PBCLK (SYSCLK / (1 << OSCCONbits.PBDIV))

#endif

//------------------------------------------------------------------------------
// End of file
