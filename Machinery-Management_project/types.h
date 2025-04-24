#pragma once

#define MAX_USERS 3
#define MAX_LOGINS 3
#define MAX_STRING 100
#define CREDENTIALS_LEN 7

#define LOGIN_PATH "users.txt"
#define DB_PATH    "fleet.txt"


typedef enum MachineType {
    TRACTOR = 1,
    EXCAVATOR = 2,
    ROLLER = 3,
    CRANE = 4,
    MIXER = 5
} MachineType;

typedef enum BreakdownFreq {
    NEVER = 1,
    LESS_THAN_THREE = 2,
    LESS_THAN_FIVE = 3,
    MORE_THAN_FIVE = 4
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

struct MachineDBNode;

typedef struct MachineDBNode {
	Machine data;
	struct MachineDBNode* next;
} MachineDBNode;


typedef struct {
    char username[MAX_STRING];
    char password[CREDENTIALS_LEN];
} User;

typedef enum ValidationResult {
    VALIDATION_OK = 0,
    ERROR_CHASSIS = 1,
    ERROR_MAKE    = 2,
    ERROR_MODEL   = 3,
    ERROR_EMAIL   = 4,
    ERROR_MILEAGE = 5,
    ERROR_OWNER   = 6,
    ERROR_PHONE   = 7
} ValidationResult;