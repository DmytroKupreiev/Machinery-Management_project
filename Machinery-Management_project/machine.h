#pragma once

#include "constants.h"

typedef enum MachineType {
    TRACTOR    = 1,
    EXCAVATOR  = 2,
    ROLLER     = 3,
    CRANE      = 4,
    MIXER      = 5
} MachineType;

typedef enum BreakdownFreq {
    NEVER           = 1,
    LESS_THAN_THREE = 2,
    LESS_THAN_FIVE  = 3,
    MORE_THAN_FIVE  = 4
} BreakdownFreq;

typedef struct Machine {
    char   chassisNumber[MAX_STRING];
    char   make[MAX_STRING];
    char   model[MAX_STRING];
    int    yearOfManufacture;
    float  cost;
    float  currentValuation;
    int    currentMileage;
    int    nextServiceMileage;
    char   ownerName[MAX_STRING];
    char   ownerEmail[MAX_STRING];
    char   ownerPhone[MAX_STRING];
    MachineType     machineType;
    BreakdownFreq   breakdowns;
} Machine;

const char* getMachineTypeString(MachineType mType);
const char* getBreakdownFreqString(BreakdownFreq bType);