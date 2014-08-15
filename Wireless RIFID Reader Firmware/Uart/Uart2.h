/*
 * File:   Uart2.h
 * Author: Seb Madgwick
 */

#ifndef UART2_H
#define UART2_H

//------------------------------------------------------------------------------
// Includes

#include <plib.h>

//------------------------------------------------------------------------------
// Function declarations

void Uart2Initialise(const UINT32 baudRate, const BOOL ctsRtsEnabled);
unsigned int Uart2IsGetReady();
char Uart2GetChar();
unsigned int Uart2IsPutReady();
void Uart2PutChar(const char c);
void Uart2PutString(const char* string);
void Uart2ClearRxBuffer();
void Uart2ClearTxBuffer();
BOOL Uart2GetRxBufferOverrunFlag();
void Uart2ClearRxBufferOverrunFlag();
BOOL Uart2TxIsIdle();

#endif

//------------------------------------------------------------------------------
// End of file
