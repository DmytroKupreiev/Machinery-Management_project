#pragma once

#include "constants.h"

typedef enum MachineType {
    TRACTOR = 1,
    EXCAVATOR,
    ROLLER,
    CRANE,
    MIXER
} MachineType;

typedef enum BreakdownFreq {
    NEVER = 1,
    LESS_THAN_THREE,
    LESS_THAN_FIVE,
    MORE_THAN_FIVE
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