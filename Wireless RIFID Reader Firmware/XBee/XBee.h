/*
 * File:   XBee.h
 * Author: Seb Madgwick
 *
 */

#ifndef XBEE_H
#define XBEE_H

//------------------------------------------------------------------------------
// Includes

#include <stddef.h>

//------------------------------------------------------------------------------
// Function declarations

void XBeeInitialise();
void XBeeDoTasks();
size_t XBeeIsGetReady();
char XBeeGetChar();
void XBeePutCharArray(const char* const source, size_t sourceSize);
void XBeeSetSleepState(const BOOL enabled);

#endif

//------------------------------------------------------------------------------
// End of file
