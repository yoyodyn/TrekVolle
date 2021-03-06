#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <pebble.h>
#include "weather.h"
#include "network.h"
#include "battery.h"
#include "configuration.h"
#include "acceleration.h"

#ifdef DEBUG_ENABLED
   #define DEBUG_COMMUNICATION
#endif

// Lots of defines....
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define KEY_ICON 2
#define KEY_LOCATION 3

#define KEY_ONLINE 4

#define KEY_BATTERY_CHARGE 5
#define KEY_BATTERY_STATE 6

#define KEY_COLOR_BACKGROUND 7
#define KEY_COLOR_TEXT 8
#define KEY_COLOR_IMAGE 9
#define KEY_COLOR_WINDOW 10
#define KEY_COLOR_CHARGING 11
#define KEY_COLOR_ERROR 12 
#define KEY_COLOR_BATTERYLOW 13
#define KEY_COLOR_CLOCK_HOUR 27
#define KEY_COLOR_CLOCK_MIN 28

#define KEY_WEATHER_TEMPERATURECELCIUS 14
#define KEY_WEATHER_REFRESHTIME 20
#define KEY_WEATHER_RETRYUPDATE 21
#define KEY_WEATHER_TEMPERATURE_MIN 24
#define KEY_WEATHER_TEMPERATURE_MAX 25

#define KEY_CLOCK_CLOCK24H 15
#define KEY_CLOCK_DATESTYLE 16
#define KEY_CLOCK_SLEEP 22
#define KEY_CLOCK_DAYOFYEARSTYLE 26

#define KEY_NETWORK_REFRESHTIME 17
#define KEY_NETWORK_VIBRATIONENABLED 19

#define KEY_BLUETOOTH_VIBRATIONENABLED 18

#define KEY_PINGPONG 23
#define KEY_ACCELERATION_ENABLE 29


// Functions used in other files 

bool m_b_CommunicationIsInit;

void Communication_Send(int i_MessageID);
void Communication_Init();
void Communication_OnInit();
void Communication_DeInit();

#endif