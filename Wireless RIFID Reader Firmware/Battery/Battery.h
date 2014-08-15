/*
 * File:   Battery.h
 * Author: Seb Madgwick
 */

#ifndef BATTERY_H
#define BATTERY_H

//------------------------------------------------------------------------------
// Definitions

typedef enum {
    NOT_CONNECTED,
    CHARGING,
    COMPLETE
} CHARGER_STATUS;

//------------------------------------------------------------------------------
// Function declarations

void BatteryInitialise();
CHARGER_STATUS BatteryGetChargerStatus();
float BatteryGetVoltage();

#endif

//------------------------------------------------------------------------------
// End of file
