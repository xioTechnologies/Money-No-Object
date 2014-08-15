/*
 * File:   Rfid.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "Uart/Uart2.h"

//------------------------------------------------------------------------------
// Variables

static char rxString[256];
static unsigned char rxStringIndex = 0;
static BOOL isGetReady = FALSE;

//------------------------------------------------------------------------------
// Functions

void RfidInitialise(void) {
    Uart2Initialise(9600, FALSE);
}

void RfidDoTasks(void) {

    // Fetch received bytes from UART
    while (Uart2IsGetReady() > 0) {
        rxString[rxStringIndex++] = Uart2GetChar();
    }

    // Check if reception complete
    if (rxStringIndex > 0) {
        if (rxString[rxStringIndex - 1] == 0x03) {
            rxString[rxStringIndex] = '\0'; // terminate as string
            rxStringIndex = 0; // reset index
            isGetReady = TRUE;
        }
    }
}

BOOL RfidIsGetReady(void) {
    return isGetReady;
}

void RfidIsGetString(char* const dest, size_t maxSize) {
    int i = 0;
    int j = 0;

    while (rxString[j++] != '\r'); // advance j to end of id string
    j -= 13;

    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = rxString[j++];
    dest[i++] = '\0';

    isGetReady = FALSE;
}

//------------------------------------------------------------------------------
// End of file
