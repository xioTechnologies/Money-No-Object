/*
 * File:   NeoPixels.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "NeoPixels/NeoPixels.h"
#include "SystemClock.h"

//------------------------------------------------------------------------------
// Definitions

#define INT_PRIORITY_LEVEL_X INT_PRIORITY_LEVEL_7
#define IPLXSOFT IPL7SOFT

//------------------------------------------------------------------------------
// Variables

static volatile int spiBuffer[MAX_NUM_NEOPIXELS * 3];
static volatile unsigned int spiBufferIndex;
static volatile unsigned int spiBufferCount;

//------------------------------------------------------------------------------
// Functions

void NeoPixelsInitialise(void) {

    // Setup SPI
    INTSetVectorPriority(INT_VECTOR_SPI(SPI_CHANNEL1), INT_PRIORITY_LEVEL_X);
    SpiChnOpen(SPI_CHANNEL1, SPI_OPEN_MSTEN | SPI_OPEN_MODE32 | SPI_CONFIG2_IGNROV | SPI_CONFIG_CKP_HIGH, PBCLK / 3200000); // 3.2 MHz SPI clock = 800 kHz bitstream

    // Turn all LEDs off
    NeoPixelsAllOff();
}

void NeoPixelsWrite(const NEOPIXEL * const neoPixels, unsigned int numNeoPixels) {
    volatile int* spiBufferPtr = spiBuffer;

    // Abort if previous send still in progress
    if (INTGetEnable(INT_SOURCE_SPI(SPI_CHANNEL1))) {
        return;
    }

    // Ignore excess pixels
    if (numNeoPixels > 3 * MAX_NUM_NEOPIXELS) {
        numNeoPixels = 3 * MAX_NUM_NEOPIXELS;
    }

    *spiBufferPtr = 0x00000000;
    spiBufferPtr++;

    // Buffer SPI data
    int i;
    for (i = 0; i < numNeoPixels; i++) {

        // Green
        *spiBufferPtr = 0x88888888;
        if (neoPixels[i].green & (0x80 >> 0)) *spiBufferPtr |= 0xE0000000;
        if (neoPixels[i].green & (0x80 >> 1)) *spiBufferPtr |= 0x0E000000;
        if (neoPixels[i].green & (0x80 >> 2)) *spiBufferPtr |= 0x00E00000;
        if (neoPixels[i].green & (0x80 >> 3)) *spiBufferPtr |= 0x000E0000;
        if (neoPixels[i].green & (0x80 >> 4)) *spiBufferPtr |= 0x0000E000;
        if (neoPixels[i].green & (0x80 >> 5)) *spiBufferPtr |= 0x00000E00;
        if (neoPixels[i].green & (0x80 >> 6)) *spiBufferPtr |= 0x000000E0;
        if (neoPixels[i].green & (0x80 >> 7)) *spiBufferPtr |= 0x0000000E;
        spiBufferPtr++;

        // Red
        *spiBufferPtr = 0x88888888;
        if (neoPixels[i].red & (0x80 >> 0)) *spiBufferPtr |= 0xE0000000;
        if (neoPixels[i].red & (0x80 >> 1)) *spiBufferPtr |= 0x0E000000;
        if (neoPixels[i].red & (0x80 >> 2)) *spiBufferPtr |= 0x00E00000;
        if (neoPixels[i].red & (0x80 >> 3)) *spiBufferPtr |= 0x000E0000;
        if (neoPixels[i].red & (0x80 >> 4)) *spiBufferPtr |= 0x0000E000;
        if (neoPixels[i].red & (0x80 >> 5)) *spiBufferPtr |= 0x00000E00;
        if (neoPixels[i].red & (0x80 >> 6)) *spiBufferPtr |= 0x000000E0;
        if (neoPixels[i].red & (0x80 >> 7)) *spiBufferPtr |= 0x0000000E;
        spiBufferPtr++;

        // Blue
        *spiBufferPtr = 0x88888888;
        if (neoPixels[i].blue & (0x80 >> 0)) *spiBufferPtr |= 0xE0000000;
        if (neoPixels[i].blue & (0x80 >> 1)) *spiBufferPtr |= 0x0E000000;
        if (neoPixels[i].blue & (0x80 >> 2)) *spiBufferPtr |= 0x00E00000;
        if (neoPixels[i].blue & (0x80 >> 3)) *spiBufferPtr |= 0x000E0000;
        if (neoPixels[i].blue & (0x80 >> 4)) *spiBufferPtr |= 0x0000E000;
        if (neoPixels[i].blue & (0x80 >> 5)) *spiBufferPtr |= 0x00000E00;
        if (neoPixels[i].blue & (0x80 >> 6)) *spiBufferPtr |= 0x000000E0;
        if (neoPixels[i].blue & (0x80 >> 7)) *spiBufferPtr |= 0x0000000E;
        spiBufferPtr++;
    }

    *spiBufferPtr = 0x00000000;
    spiBufferPtr++;

    // Start send
    spiBufferIndex = 0;
    spiBufferCount = spiBufferPtr - spiBuffer;
    INTSetFlag(INT_SOURCE_SPI(SPI_CHANNEL1)); // trigger first interrupt
    INTEnable(INT_SOURCE_SPI(SPI_CHANNEL1), INT_ENABLED); // enable interrupts
}

void NeoPixelsAllOff(void) {
    int i;
    NEOPIXEL pixels[MAX_NUM_NEOPIXELS];
    for (i = 0; i < MAX_NUM_NEOPIXELS; i++) {
        pixels[i].red = 0;
        pixels[i].green = 0;
        pixels[i].blue = 0;
    }
    NeoPixelsWrite(pixels, MAX_NUM_NEOPIXELS);
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __ISR(_SPI_1_VECTOR, IPLXSOFT) IntSpi1Handler(void) {
    INTClearFlag(INT_SOURCE_SPI(SPI_CHANNEL1)); // clear interrupt flag
    if (INTGetFlag(INT_SOURCE_SPI(SPI_CHANNEL1))) {
        if (spiBufferIndex >= spiBufferCount) { // disable further interrupts if complete
            INTEnable(INT_SOURCE_SPI(SPI_CHANNEL1), INT_DISABLED);
        } else {
            SpiChnPutC(SPI_CHANNEL1, spiBuffer[spiBufferIndex++]);
        }
    }
}

//------------------------------------------------------------------------------
// End of file
