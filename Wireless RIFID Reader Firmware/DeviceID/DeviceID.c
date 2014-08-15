/*
 * File:   DeviceID.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
// Variables

static char id; // only lower nibble used

//------------------------------------------------------------------------------
// Functions

void DeviceIDInitialise() {
    id = (~mPORTBRead() >> 2) & 0xF;
}

unsigned char DeviceIDGetID() {
    if (id == 0) {
        return 1 + (rand() & 0b11);
    } else {

    }
}

//------------------------------------------------------------------------------
// End of file
