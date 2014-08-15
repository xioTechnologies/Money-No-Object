/*
 * File:   Uart1.c
 * Author: Seb Madgwick
 *
 * RX_BUFFER_SIZE and TX_BUFFER_SIZE must be a 2^n number, e.g. 256, 512, 1024.
 *
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "SystemClock.h"
#include "Uart1.h"

//------------------------------------------------------------------------------
// Definitions

#define RX_BUFFER_SIZE 1024
#define TX_BUFFER_SIZE 1024
#define INT_PRIORITY_LEVEL_X INT_PRIORITY_LEVEL_2
#define IPLXSOFT IPL2SOFT

//------------------------------------------------------------------------------
// Variables

static volatile char rxBuffer[RX_BUFFER_SIZE];
static volatile unsigned int rxBufferIn = 0;
static volatile unsigned int rxBufferOut = 0;
static volatile int rxBufferOverrun = FALSE;
static volatile char txBuffer[TX_BUFFER_SIZE];
static volatile unsigned int txBufferIn = 0;
static volatile unsigned int txBufferOut = 0;

//------------------------------------------------------------------------------
// Functions

void Uart1Initialise(const UINT32 baudRate, const BOOL ctsRtsEnabled) {
    if (ctsRtsEnabled) {
        UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY | UART_ENABLE_PINS_CTS_RTS | UART_ENABLE_HIGH_SPEED);
    } else {
        UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY | UART_ENABLE_HIGH_SPEED);
    }
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_BUFFER_EMPTY);
    UARTSetDataRate(UART1, PBCLK, baudRate);
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_X);
    INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);
}

unsigned int Uart1IsGetReady() {
    if (UARTReceivedDataIsAvailable(UART1)) { // trigger interrupt if data available
        INTSetFlag(INT_SOURCE_UART_RX(UART1));
    }
    if (UARTGetLineStatus(UART1) & UART_OVERRUN_ERROR) {
        U1STACLR = UART_OVERRUN_ERROR; // clear flag and re-enable UART if hardware buffer overrun
    }
    return (rxBufferIn - rxBufferOut) & (RX_BUFFER_SIZE - 1);
}

char Uart1GetChar() {
    char c = rxBuffer[rxBufferOut++];
    rxBufferOut &= (RX_BUFFER_SIZE - 1); // overflow index at buffer size
    return c;
}

unsigned int Uart1IsPutReady() {
    return (TX_BUFFER_SIZE - 1) - ((txBufferIn - txBufferOut) & (TX_BUFFER_SIZE - 1));
}

void Uart1PutChar(const char c) {
    txBuffer[txBufferIn++] = c;
    txBufferIn &= (TX_BUFFER_SIZE - 1); // overflow index at buffer size
    if (!INTGetEnable(INT_SOURCE_UART_TX(UART1))) {
        INTSetFlag(INT_SOURCE_UART_TX(UART1));
        INTEnable(INT_SOURCE_UART_TX(UART1), INT_ENABLED);
    }
}

void Uart1PutString(const char* string) {
    while (*string != '\0') {
        Uart1PutChar(*string++);
    }
}

void Uart1ClearRxBuffer() {
    rxBufferIn = rxBufferOut;
    rxBufferOverrun = FALSE;
}

void Uart1ClearTxBuffer() {
    txBufferOut = txBufferIn;
}

BOOL Uart1GetRxBufferOverrunFlag() {
    return rxBufferOverrun;
}

void Uart1ClearRxBufferOverrunFlag() {
    rxBufferOverrun = FALSE;
}

BOOL Uart1TxIsIdle() {
    return !INTGetEnable(INT_SOURCE_UART_TX(UART1));
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __ISR(_UART_1_VECTOR, IPLXSOFT) IntUart1Handler(void) {

    // RX interrupt
    if (INTGetFlag(INT_SOURCE_UART_RX(UART1))) {
        while (UARTReceivedDataIsAvailable(UART1)) { // repeat while data available
            rxBuffer[rxBufferIn++] = UARTGetDataByte(UART1); // fetch data from hardware buffer and increment index
            rxBufferIn &= (RX_BUFFER_SIZE - 1); // overflow index at buffer size
            if (rxBufferIn == rxBufferOut) { // check for rxBuffer overrun
                rxBufferOverrun = TRUE;
            }
        }
        INTClearFlag(INT_SOURCE_UART_RX(UART1)); // data received immediately before clearing UxRXIF will be unhandled, URXDA must be polled to set UxRXIF
    }

    // TX interrupt
    if (INTGetFlag(INT_SOURCE_UART_TX(UART1))) {
        INTEnable(INT_SOURCE_UART_TX(UART1), INT_DISABLED); // disable interrupt to avoid nested interrupt
        INTClearFlag(INT_SOURCE_UART_TX(UART1)); // clear interrupt flag
        do {
            if (txBufferOut == txBufferIn) { // if txBuffer empty
                return;
            }
            UARTSendDataByte(UART1, txBuffer[txBufferOut++]); // send data to hardware buffer and increment index
            txBufferOut &= (TX_BUFFER_SIZE - 1); // overflow index at buffer size
        } while (!UARTTransmitterIsReady(UART1)); // repeat while hardware buffer not full
        INTEnable(INT_SOURCE_UART_TX(UART1), INT_ENABLED); // re-enable interrupt
    }
}

//------------------------------------------------------------------------------
// End of file
