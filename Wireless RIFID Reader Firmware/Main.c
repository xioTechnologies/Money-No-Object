/*
 * File:   Main.c
 * Author: Seb Madgwick
 *
 * Device:
 * PIC32MX450F256H
 *
 * Compiler:
 * XC32 v1.32
 *
 * Peripherals used:
 * Core timer           Delay.c
 * SPI1                 NeoPixels.c
 * UART1                Uart1.c
 * UART2                Uart2.c
 *
 * Interrupt priorities (nesting enabled):
 * 7. SPI1 (NeoPixels.c)
 * 6.
 * 5.
 * 4.
 * 3. Input change notification (Rfid.c)
 * 2. UART1 (Uart1.c), UART2 (Uart2.c)
 * 1.
 */

//------------------------------------------------------------------------------
// Includes

#include "Animations/Animations.h"
#include "Battery/Battery.h"
#include "DeviceID/DeviceID.h"
#include "FirmwareVersion.h"
#include <plib.h>
#include "Rfid/Rfid.h"
#include "SleepTimer/SleepTimer.h"
#include "SystemClock.h"
#include "NeoPixels/NeoPixels.h"
#include "XBee/XBee.h"

//------------------------------------------------------------------------------
// Configuration Bits

#pragma config FNOSC = FRCPLL // Fast RC Oscillator with divide-by-N with PLL module
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1 // SYSCLK = 80 MHz
#pragma config FSOSCEN = OFF // Disable Secondary Oscillator
#pragma config FWDTEN = OFF // Watchdog Timer is not enabled
#pragma config JTAGEN = OFF // JTAG is disabled
#pragma config ICESEL = ICS_PGx1 // PGEC1/PGED1 pair is used
#pragma config OSCIOFNC = ON // CLKO output signal active on the OSCO pin

//------------------------------------------------------------------------------
// Function declarations

static void Initialise();

//------------------------------------------------------------------------------
// Functions

int main(void) {

    // Initialise PIC32MX
    Initialise();

    // Initialise modules
    DeviceIDInitialise();
    RfidInitialise();
    XBeeInitialise();
    NeoPixelsInitialise();
    BatteryInitialise();
    SleepTimerInitialise();
    AnimiationInitialise();

    // Start up tasks
    {
        SleepTimerReset();
        char string[256];
        sprintf(string, "%d,%s%s,%f\n", DeviceIDGetID(), "Firmware ", FIRMWARE_VERSION, BatteryGetVoltage());
        XBeePutCharArray(string, strlen(string));
        AnimationsPlay();
    }

    // Main loop
    while (TRUE) {

        // Module tasks
        RfidDoTasks();
        XBeeDoTasks();
        SleepTimerDoTasks();
        AnimationsDoTasks();

        // Application tasks
        if (RfidIsGetReady()) {
            SleepTimerReset();
            char rfidString[16];
            RfidIsGetString(rfidString, sizeof (rfidString));
            char string[256];
            sprintf(string, "%d,%s,%f\n", DeviceIDGetID(), rfidString, BatteryGetVoltage());
            XBeePutCharArray(string, strlen(string));
            AnimationsPlay();
        }
    }
}

static void Initialise() {

    // Configure CPU
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();

    // Configure pull ups/downs
    CNPDFSET = 0x00000020; // RF5 is VBUS
    CNPUBSET = 0x0000403C; // RB2-5 are SEL0-3, RB14 is charger STAT

    // Configure output states
    mPORTDSetBits(BIT_3); // RD3 is XBee DOUT (U1TX)
    mPORTDSetBits(BIT_5); // RD5 is XBee RTS (U1RTS)
    mPORTDSetBits(BIT_6); // RD6 is XBee Reset
    mPORTESetBits(BIT_5); // RE5 is NeoPixels enable
    mPORTCClearBits(BIT_13); // RC13 is NeoPixels DIN (SDO1).  Why is this bit set after reset?

    // Configure I/O directions
    mPORTDSetPinsDigitalOut(BIT_0); // RD0 is external trigger/debugging pin
    mPORTCSetPinsDigitalIn(BIT_14); // RC14 is XBee DOUT (U1RX)
    mPORTDSetPinsDigitalOut(BIT_3); // RD3 is XBee DIN (U1TX)
    mPORTDSetPinsDigitalIn(BIT_4); // RD4 is XBee CTS (U1CTS)
    mPORTDSetPinsDigitalOut(BIT_5); // RD5 is XBee RTS (U1RTS)
    mPORTDSetPinsDigitalOut(BIT_6); // RD6 is XBee Reset
    mPORTDSetPinsDigitalOut(BIT_7); // RD7 is XBee Sleep
    mPORTDSetPinsDigitalIn(BIT_10); // RD10 is ID-3LA (U2RX)
    mPORTESetPinsDigitalOut(BIT_5); // RE5 is NeoPixels enable
    mPORTCSetPinsDigitalOut(BIT_13); // RC13 is NeoPixels DIN (SDO1)
    mPORTBSetPinsAnalogIn(BIT_15); // RB15 is battery level (AN15)
    mPORTFSetPinsDigitalIn(BIT_5); // RF5 is VBUS
    mPORTBSetPinsDigitalIn(BIT_14); // B14 is charger STAT
    mPORTBSetPinsDigitalIn(BIT_2); // RB2 are SEL0
    mPORTBSetPinsDigitalIn(BIT_3); // RB3 are SEL1
    mPORTBSetPinsDigitalIn(BIT_4); // RB4 are SEL2
    mPORTBSetPinsDigitalIn(BIT_5); // RB5 are SEL3

    // Map peripherals
    PPSInput(1, U1RX, RPC14); // RPC14 is XBee DOUT (U1RX)
    PPSOutput(2, RPD3, U1TX); // RPD3 is XBee DIN (U1TX)
    PPSInput(3, U1CTS, RPD4); // RPD4 is XBee CTS (U1CTS)
    PPSOutput(4, RPD5, U1RTS); // RPD5 is XBee RTS (U1RTS)
    PPSInput(1, U2RX, RPD10); // RPD10 is ID-3LA (U2RX)
    PPSOutput(2, RPC13, SDO1); // RPC13 is NeoPixels DIN (SDO1)
}

//------------------------------------------------------------------------------
// End of file
