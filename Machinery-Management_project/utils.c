#include "utils.h"

const char* getMachineTypeString(MachineType mType) {
    switch (mType) {
        case TRACTOR:   return "Tractor";
        case EXCAVATOR: return "Excavator";
        case ROLLER:    return "Roller";
        case CRANE:     return "Crane";
        case MIXER:     return "Mixer";
        default:        return "Unknown";
    }
}

const char* getBreakdownFreqString(BreakdownFreq bType) {
    switch (bType) {
        case NEVER:           return "Never";
        case LESS_THAN_THREE: return "Less than 3";
        case LESS_THAN_FIVE:  return "Less than 5";
        case MORE_THAN_FIVE:  return "More than 5";
        default:              return "Unknown";
    }
}
