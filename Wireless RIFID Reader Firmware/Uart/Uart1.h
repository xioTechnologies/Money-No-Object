/*
 * File:   Uart1.h
 * Author: Seb Madgwick
 */

#ifndef UART1_H
#define UART1_H

//------------------------------------------------------------------------------
// Includes

#include <plib.h>

//------------------------------------------------------------------------------
// Function declarations

void Uart1Initialise(const UINT32 baudRate, const BOOL ctsRtsEnabled);
unsigned int Uart1IsGetReady();
char Uart1GetChar();
unsigned int Uart1IsPutReady();
void Uart1PutChar(const char c);
void Uart1PutString(const char* string);
void Uart1ClearRxBuffer();
void Uart1ClearTxBuffer();
BOOL Uart1GetRxBufferOverrunFlag();
void Uart1ClearRxBufferOverrunFlag();
BOOL Uart1TxIsIdle();

#endif

//------------------------------------------------------------------------------
// End of file
