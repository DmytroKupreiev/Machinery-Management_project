#include "utils.h"

#include <string.h>

// convert to string for output
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

int validateMachine(const Machine* machine) {
    if (strlen(machine->chassisNumber) == 0) return ERROR_CHASSIS;
    if (strlen(machine->make) == 0)          return ERROR_MAKE;
    if (strlen(machine->model) == 0)         return ERROR_MODEL;
    if (strlen(machine->ownerEmail) == 0)    return ERROR_EMAIL;
    if (strlen(machine->ownerName) == 0)     return ERROR_OWNER;
    if (strlen(machine->ownerPhone) == 0)    return ERROR_PHONE;
    if (machine->currentMileage < 0)         return ERROR_MILEAGE;

    return VALIDATION_OK;
}

// Error notification
const char* getValidationError(ValidationResult result) {
    const char* errors[] = {
        "\n(+) All fields are valid",
        "\n(-) Error: Chassis Number is required!",
        "\n(-) Error: Make is required!",
        "\n(-) Error: Model is required!",
        "\n(-) Error: Email is required!",
        "\n(-) Error: Current Mileage must be positive!",
        "\n(-) Error: Owner is required!",
        "\n(-) Error: Phone is required!"
    };

    return errors[result];
}