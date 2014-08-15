/*
 * File:   XBee.c
 * Author: Seb Madgwick
 *
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay\Delay.h"
#include <plib.h>
#include "Uart/Uart1.h"
#include "XBee.h"

//------------------------------------------------------------------------------
// Definitions

#define RESET_PIN_LOW() { mPORTDClearBits(BIT_6); }
#define RESET_PIN_HIGH() { mPORTDSetBits(BIT_6); }
#define SLEEP_PIN_LOW() { mPORTDClearBits(BIT_7); }
#define SLEEP_PIN_HIGH() { mPORTDSetBits(BIT_7); }

//------------------------------------------------------------------------------
// Variables

static char rxBuffer[256]; // size of 256 for automatic index wrap around with unsigned char
static unsigned char rxBufferIn = 0;
static unsigned char rxBufferOut = 0;

//------------------------------------------------------------------------------
// Functions

void XBeeInitialise(void) {

    // Reset XBee module.  Why don't XBee settings revert to defaults here?
    RESET_PIN_LOW();
    DelayMs(1); // wait at least 200 ns
    RESET_PIN_HIGH();

    // Put XBee in command mode
    Uart1Initialise(9600, TRUE); // init UART for 9600
    DelayMs(1050);
    Uart1PutString("+++");
    DelayMs(1050);

    // Configure XBee
    Uart1PutString("ATSM1\r"); // set sleep mode
    DelayMs(10);
    Uart1PutString("ATBD3D090\r"); // set baud rate to 250000
    DelayMs(10);
    Uart1PutString("ATAP1\r"); // set API mode
    DelayMs(10);
    Uart1PutString("ATCN\r"); // exit command mode
    DelayMs(10);
    Uart1Initialise(250000, TRUE);

    // Clear receive buffer
    DelayMs(10);
    Uart1ClearRxBuffer();
}

void XBeeDoTasks(void) {
    while (Uart1IsGetReady()) {
        static BOOL waitingForDelimiter = TRUE;
        if (waitingForDelimiter) {
            if (Uart1GetChar() == 0x7E) {
                rxBufferIn = 0;
                rxBufferOut = 0;
                rxBuffer[rxBufferIn++] = 0x7E;
                waitingForDelimiter = FALSE;
            }
        } else {
            rxBuffer[rxBufferIn++] = Uart1GetChar();
            do {
                int i = 3;
                unsigned char checksum = 0;
                if (rxBufferIn < 10) { // if too short for decoding
                    break;
                }
                if (rxBufferIn - 4 > (unsigned char) rxBuffer[2]) { // if too many bytes
                    waitingForDelimiter = TRUE;
                    break;
                }
                if (rxBufferIn - 4 < (unsigned char) rxBuffer[2]) { // if too few bytes
                    break;
                }
                while (i < rxBufferIn) {
                    checksum += rxBuffer[i++];
                }
                if (checksum != 0xFF) { // if checksum invalid
                    break;
                }
                if ((unsigned char) rxBuffer[3] != 0x81) { // if incorrect API identifier
                    break;
                }
                waitingForDelimiter = TRUE;
                rxBufferOut = 8; // start index of payload
                rxBufferIn--; // end index before checksum
                return;
            } while (0);
        }
    }
}

size_t XBeeIsGetReady() {
    if (rxBufferOut == 0) {
        return 0;
    } else {
        return rxBufferIn - rxBufferOut;
    }
}

char XBeeGetChar() {
    unsigned char c = rxBuffer[rxBufferOut++];
    if (rxBufferOut == rxBufferIn) {
        rxBufferOut = 0;
    }
    return c;
}

void XBeePutCharArray(const char* const source, size_t sourceSize) {
    int i = 0;

    // Discard data if UART not ready
    if (sourceSize + 9 > Uart1IsPutReady()) {
        return;
    }

    // Parse bytes in TX request packet
    char sum = 0x02;
    char length = 5 + sourceSize;
    Uart1PutChar(0x7E); // start delimiter
    Uart1PutChar(length >> 8);
    Uart1PutChar(length & 0xFF);
    Uart1PutChar(0x01); // API identifier
    Uart1PutChar(0x00); // disable response frame
    Uart1PutChar(0x00); // destination address MSB
    Uart1PutChar(0x00); // destination address LSB
    Uart1PutChar(0x01); // disable ACK
    while (i < sourceSize) { // RF data
        Uart1PutChar(source[i]);
        sum += source[i];
        i++;
    }
    Uart1PutChar(0xFF - sum); // checksum
}

void XBeeSetSleepState(const BOOL enabled) {
    if (enabled) {
        SLEEP_PIN_HIGH();
    } else {
        SLEEP_PIN_LOW();
    }
}

//------------------------------------------------------------------------------
// End of file
