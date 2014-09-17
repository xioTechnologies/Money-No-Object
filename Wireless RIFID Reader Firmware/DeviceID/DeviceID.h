/*
 * File:   DeviceID.h
 * Author: Seb Madgwick
 */

#ifndef DEVICEID_H
#define DEVICEID_H

//------------------------------------------------------------------------------
// Definitions

typedef enum {
    HANDSHAKE = 1,
    HIGH_FIVE,
    HUG,
    TAP,
} DEVICE_ID;

//------------------------------------------------------------------------------
// Function declarations

void DeviceIDInitialise();
unsigned char DeviceIDGetID();
void DeviceIDGetString(char* const dest);

#endif

//------------------------------------------------------------------------------
// End of file
