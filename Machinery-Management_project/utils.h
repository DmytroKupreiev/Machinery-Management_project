#include "types.h"

const char* getMachineTypeString(MachineType mType);
const char* getBreakdownFreqString(BreakdownFreq bType);
const char* getValidationError(ValidationResult result);
int validateMachine(const Machine* machine);