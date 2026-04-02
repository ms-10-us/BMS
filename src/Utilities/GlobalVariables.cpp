#include "../../include/BMS/GlobalVariables.h"

GlobalVariables globalVariables = {
    .GlobalCapacityAh = 2.5,
    .GlobalR0 = 0.01,
    .GlobalR1 = 0.02,
    .GlobalC1 = 2000.0,
    .GlobalInitialSOC = 1.0,
    .GlobalSimTime = 10,
    .GlobalTimeStep = 0.1,
    .GlobalCellMass = 0.05,
    .GlobalCellCp = 900,
    .GlobalInitialTemperature = 25,
    .TestCurrent = 2,
    .ThreadSleepTime = 1000};