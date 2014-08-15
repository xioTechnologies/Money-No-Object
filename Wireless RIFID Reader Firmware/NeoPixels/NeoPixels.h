/*
 * File:   NeoPixels.h
 * Author: Seb Madgwick
 */

#ifndef NEOPIXELS_H
#define NEOPIXELS_H

//------------------------------------------------------------------------------
// Definitions

#define MAX_NUM_NEOPIXELS 16

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} NEOPIXEL;

//------------------------------------------------------------------------------
// Function declarations

void NeoPixelsInitialise(void);
void NeoPixelsWrite(const NEOPIXEL * const neoPixels, unsigned int numNeoPixels);
void NeoPixelsAllOff(void);

#endif

//------------------------------------------------------------------------------
// End of file
