/*
 * File:   Uart2.c
 * Author: Seb Madgwick
 *
 * RX_BUFFER_SIZE and TX_BUFFER_SIZE must be a 2^n number, e.g. 256, 512, 1024.
 *
 */

//------------------------------------------------------------------------------
// Includes

#include <plib.h>
#include "SystemClock.h"
#include "Uart2.h"

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

void Uart2Initialise(const UINT32 baudRate, const BOOL ctsRtsEnabled) {
    if (ctsRtsEnabled) {
        UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY | UART_ENABLE_PINS_CTS_RTS | UART_ENABLE_HIGH_SPEED);
    } else {
        UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY | UART_ENABLE_HIGH_SPEED);
    }
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_TX_BUFFER_EMPTY);
    UARTSetDataRate(UART2, PBCLK, baudRate);
    UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_X);
    INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
}

unsigned int Uart2IsGetReady() {
    if (UARTReceivedDataIsAvailable(UART2)) { // trigger interrupt if data available
        INTSetFlag(INT_SOURCE_UART_RX(UART2));
    }
    if (UARTGetLineStatus(UART2) & UART_OVERRUN_ERROR) {
        U2STACLR = UART_OVERRUN_ERROR; // clear flag and re-enable UART if hardware buffer overrun
    }
    return (rxBufferIn - rxBufferOut) & (RX_BUFFER_SIZE - 1);
}

char Uart2GetChar() {
    char c = rxBuffer[rxBufferOut++];
    rxBufferOut &= (RX_BUFFER_SIZE - 1); // overflow index at buffer size
    return c;
}

unsigned int Uart2IsPutReady() {
    return (TX_BUFFER_SIZE - 1) - ((txBufferIn - txBufferOut) & (TX_BUFFER_SIZE - 1));
}

void Uart2PutChar(const char c) {
    txBuffer[txBufferIn++] = c;
    txBufferIn &= (TX_BUFFER_SIZE - 1); // overflow index at buffer size
    if (!INTGetEnable(INT_SOURCE_UART_TX(UART2))) {
        INTSetFlag(INT_SOURCE_UART_TX(UART2));
        INTEnable(INT_SOURCE_UART_TX(UART2), INT_ENABLED);
    }
}

void Uart2PutString(const char* string) {
    while (*string != '\0') {
        Uart2PutChar(*string++);
    }
}

void Uart2ClearRxBuffer() {
    rxBufferIn = rxBufferOut;
    rxBufferOverrun = FALSE;
}

void Uart2ClearTxBuffer() {
    txBufferOut = txBufferIn;
}

BOOL Uart2GetRxBufferOverrunFlag() {
    return rxBufferOverrun;
}

void Uart2ClearRxBufferOverrunFlag() {
    rxBufferOverrun = FALSE;
}

BOOL Uart2TxIsIdle() {
    return !INTGetEnable(INT_SOURCE_UART_TX(UART2));
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __ISR(_UART_2_VECTOR, IPLXSOFT) IntUart2Handler(void) {

    // RX interrupt
    if (INTGetFlag(INT_SOURCE_UART_RX(UART2))) {
        while (UARTReceivedDataIsAvailable(UART2)) { // repeat while data available
            rxBuffer[rxBufferIn++] = UARTGetDataByte(UART2); // fetch data from hardware buffer and increment index
            rxBufferIn &= (RX_BUFFER_SIZE - 1); // overflow index at buffer size
            if (rxBufferIn == rxBufferOut) { // check for rxBuffer overrun
                rxBufferOverrun = TRUE;
            }
        }
        INTClearFlag(INT_SOURCE_UART_RX(UART2)); // data received immediately before clearing UxRXIF will be unhandled, URXDA must be polled to set UxRXIF
    }

    // TX interrupt
    if (INTGetFlag(INT_SOURCE_UART_TX(UART2))) {
        INTEnable(INT_SOURCE_UART_TX(UART2), INT_DISABLED); // disable interrupt to avoid nested interrupt
        INTClearFlag(INT_SOURCE_UART_TX(UART2)); // clear interrupt flag
        do {
            if (txBufferOut == txBufferIn) { // if txBuffer empty
                return;
            }
            UARTSendDataByte(UART2, txBuffer[txBufferOut++]); // send data to hardware buffer and increment index
            txBufferOut &= (TX_BUFFER_SIZE - 1); // overflow index at buffer size
        } while (!UARTTransmitterIsReady(UART2)); // repeat while hardware buffer not full
        INTEnable(INT_SOURCE_UART_TX(UART2), INT_ENABLED); // re-enable interrupt
    }
}

//------------------------------------------------------------------------------
// End of file
