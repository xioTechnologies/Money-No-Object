/*
 * File:   DeviceID.h
 * Author: Seb Madgwick
 */

#ifndef DEVICEID_H
#define DEVICEID_H

//------------------------------------------------------------------------------
// Function declarations

void DeviceIDInitialise();
unsigned char DeviceIDGetID();
void DeviceIDGetString(char* const dest);

#endif

//------------------------------------------------------------------------------
// End of file
