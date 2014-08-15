/*
 * File:   Rfid.h
 * Author: Seb Madgwick
 */

#ifndef RFID_H
#define RFID_H

//------------------------------------------------------------------------------
// Function declarations

void RfidInitialise(void);
void RfidDoTasks(void);
BOOL RfidIsGetReady(void);
void RfidIsGetString(unsigned char* const dest, size_t maxSize);

#endif

//------------------------------------------------------------------------------
// End of file
