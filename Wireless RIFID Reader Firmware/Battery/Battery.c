/*
 * File:   Battery.c
 * Author: Seb Madgwick
 */

//------------------------------------------------------------------------------
// Includes

#include "Battery.h"
#include <plib.h>

//------------------------------------------------------------------------------
// Definitions

#define GET_VBUS_PIN_STATE() mPORTFReadBits(BIT_5)
#define GET_STAT_PIN_STATE() mPORTBReadBits(BIT_14)

//------------------------------------------------------------------------------
// Functions

void BatteryInitialise() {
}

CHARGER_STATUS BatteryGetChargerStatus() {
    CHARGER_STATUS chargerStatus = NOT_CONNECTED;
    if (GET_VBUS_PIN_STATE()) {
        if (GET_STAT_PIN_STATE()) {
            chargerStatus = COMPLETE;
        } else {
            chargerStatus = CHARGING;
        }
    }
    return chargerStatus;
}

float BatteryGetVoltage() {
    return 0.0f;
}

//------------------------------------------------------------------------------
// End of file
