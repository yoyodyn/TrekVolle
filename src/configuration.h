#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <pebble.h>
#include "mainwindow.h"
#include "communication.h"
#include "bluetooth.h"
#include "weather.h"
#include "network.h"
#include "clock.h"

// Variable to set the debug printout (is set in main.c)
bool m_b_Debug;

// Functions used in other files
void LoadConfigFromStorage();
void SaveConfigToStorage();
void LoadDefaultConfig();

#endif