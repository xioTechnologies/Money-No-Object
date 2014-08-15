/*
 * File:   SleepTimer.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include <Delay/Delay.h>
#include <plib.h>
#include "SleepTimer.h"
#include "SystemClock.h"

//------------------------------------------------------------------------------
// Definitions

#define SLEEP_TIMER 5000

#define DEBUG_PIN_HIGH() mPORTDSetBits(BIT_0)
#define DEBUG_PIN_LOW() mPORTDClearBits(BIT_0)
#define NEOPIXELS_ENABLE_PIN_HIGH() mPORTESetBits(BIT_5)
#define NEOPIXELS_ENABLE_PIN_LOW() mPORTEClearBits(BIT_5)

//------------------------------------------------------------------------------
// Variables

static unsigned int t = 0;

//------------------------------------------------------------------------------
// Functions

void SleepTimerInitialise(void) {
    mCNDOpen(CND_ON, CND10_ENABLE, CND_PULLUP_DISABLE_ALL);
    SleepTimerReset();
}

void SleepTimerDoTasks(void) {
    if ((ReadCoreTimer() - t) > (SLEEP_TIMER * ((SYSCLK / 2) / 1000))) {

        // Disable RFID UART RX
        UARTEnable(UART2, UART_DISABLE_FLAGS(UART_PERIPHERAL | UART_RX));

        // Enable input change notification
        ConfigIntCND(CHANGE_INT_PRI_3 | CHANGE_INT_ON);

        // Enable XBee sleep
        XBeeSetSleepState(TRUE);

        // Debug pin high
        DEBUG_PIN_LOW();

        // Disable NeoPixels
        NEOPIXELS_ENABLE_PIN_LOW();
        PPSOutput(2, RPC13, NULL); // RPC13 is not NeoPixels DIN (SDO1)

        // Enable sleep mode
        PowerSaveSleep();

        // Disable XBee sleep
        XBeeSetSleepState(FALSE);

        // Disable input change notification
        ConfigIntCND(CHANGE_INT_PRI_3 | CHANGE_INT_OFF);

        // Wait for RFID transmission of 0x02 to complete
        DelayUs(750);

        // Debug pin low
        DEBUG_PIN_HIGH();

        // Enable NeoPixels
        NEOPIXELS_ENABLE_PIN_HIGH();
        PPSOutput(2, RPC13, SDO1); // RPC13 is NeoPixels DIN (SDO1)

        // Enable RFID UART RX
        UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX));

        // Reset sleep timer
        SleepTimerReset();
    }
}

void SleepTimerReset(void) {
    t = ReadCoreTimer();
}

//------------------------------------------------------------------------------
// Functions - ISRs

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SOFT) IntChangeNoticeHandler(void) {
    INTClearFlag(INT_CND);
}

//------------------------------------------------------------------------------
// End of file
