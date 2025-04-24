#include <stdio.h> 
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "user_input.h"
#include "utils.h"
#include "types.h"

int isValidEmail(const char* email) {

    if (email == NULL || strlen(email) == 0) {
        return 0;
    }

    int atCount = 0, dotCount = 0;
    int len = strlen(email);

    if (len < 4 || strcmp(email + len - 4, ".com") != 0) {
        return 0;
    }

    for (int i = 0; i < len - 4; i++) {
        if (email[i] == '@') atCount++;
        if (email[i] == '.') dotCount++;
    }

    return (atCount == 1 && dotCount >= 1);
}

int isValidPhone(const char* phone) {
    int digitCount = 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        if (isdigit(phone[i])) digitCount++;
    }
    return (digitCount >= 7);
}

int isChassisNumberUnique(MachineDBNode* head, const char* chassisNumber) {
    MachineDBNode* current = head;
    while (current != NULL) {
        if (strcmp(current->data.chassisNumber, chassisNumber) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void inputStringWithValidation(const char* prompt, char* dest, int minLen, int maxLen) {
    do {
        printf("%s (%d-%d characters): ", prompt, minLen, maxLen);
        fgets(dest, MAX_STRING, stdin);
        dest[strcspn(dest, "\n")] = '\0';
    } while (strlen(dest) < minLen || strlen(dest) > maxLen);
}

void inputIntWithValidation(const char* prompt, int* dest, int minVal, int maxVal) {
    do {
        printf("%s (%d-%d): ", prompt, minVal, maxVal);
        int count = scanf("%d", dest);
        clearInput();
    } while (*dest < minVal || *dest > maxVal);
}

void inputFloatWithValidation(const char* prompt, float* dest, float minVal, float maxVal) {
    do {
        printf("%s (%.2f-%.2f): ", prompt, minVal, maxVal);
        int count = scanf("%f", dest);
        clearInput();
    } while (*dest < minVal || *dest > maxVal);
}

void inputEmailWithValidation(char* email) {
    do {
        printf("Enter Owner Email: ");
        fgets(email, MAX_STRING, stdin);
        email[strcspn(email, "\n")] = '\0';

        if (!isValidEmail(email)) {
            printf("Invalid email format! Must contain @, a full stop and a .com \n");
            email[0] = '\0';
        }
    } while (!isValidEmail(email));
}

void inputPhoneWithValidation(char* phone) {
    do {
        printf("Enter Owner Phone (minimum 7 digits): ");
        fgets(phone, MAX_STRING, stdin);
        phone[strcspn(phone, "\n")] = '\0';

        if (!isValidPhone(phone)) {
            printf("Invalid phone number! Must contain at least 7 digits.\n");
            phone[0] = '\0';
        }
    } while (!isValidPhone(phone));
}

void inputChassisNumber(MachineDBNode* head, char* chassisNumber) {
    do {
        printf("Enter Chassis Number (alphanumeric): ");
        fgets(chassisNumber, MAX_STRING, stdin);
        chassisNumber[strcspn(chassisNumber, "\n")] = '\0';

        printf("%s\n", chassisNumber);

        if (strlen(chassisNumber) < 1) {
            printf("Error: The chassis number must be more than 1 character long!\n");
            continue;
        }

        if (!isChassisNumberUnique(head, chassisNumber)) {
            printf("Error: This chassis number already exists in database!\n");
            chassisNumber[0] = '\0';
        }

    } while (strlen(chassisNumber) < 1 || !isChassisNumberUnique(head, chassisNumber));
}

MachineDBNode* inputMachineData(MachineDBNode** head, MachineDBNode* node)
{
    MachineDBNode* nodeToEdit;
    ValidationResult validationRes;

    if (node == NULL) {
        nodeToEdit = createRow();
    }
    else {
        nodeToEdit = node;
    }

    Machine* machine = &(nodeToEdit->data);
    int choice;

    do {
        printf("\n== Current values ==\n");
        printf("1. Chassis Number: %s\n", machine->chassisNumber);
        printf("2. Make: %s\n", machine->make);
        printf("3. Model: %s\n", machine->model);
        printf("4. Year of Manufacture: %d\n", machine->yearOfManufacture);
        printf("5. Cost: %.2f\n", machine->cost);
        printf("6. Current Valuation: %.2f\n", machine->currentValuation);
        printf("7. Current Mileage: %d\n", machine->currentMileage);
        printf("8. Next Service Mileage: %d\n", machine->nextServiceMileage);
        printf("9. Owner Name: %s\n", machine->ownerName);
        printf("10. Owner Email: %s\n", machine->ownerEmail);
        printf("11. Owner Phone: %s\n", machine->ownerPhone);
        printf("12. Machine Type: %d\n", machine->machineType);
        printf("13. Breakdown Frequency: %d\n", machine->breakdowns);
        printf("-1. Exit\n");
        printf("0. Finish and Save\n");
       
        printf("Enter field to edit: ");

        int len = scanf("%d", &choice);
        clearInput();

        switch (choice) {
        case 1:  inputChassisNumber(*head, machine->chassisNumber); break;
        case 2:  inputStringWithValidation("Enter Make", machine->make, 3, 50); break;
        case 3:  inputStringWithValidation("Enter Model", machine->model, 2, 50); break;
        case 4:  inputIntWithValidation("Enter Year of Manufacture", &machine->yearOfManufacture, 1950, 2025); break;
        case 5:  inputFloatWithValidation("Enter Cost", &machine->cost, 0, 1000000); break;
        case 6:  inputFloatWithValidation("Enter Current Valuation", &machine->currentValuation, 0, machine->cost); break;
        case 7:  inputIntWithValidation("Enter Current Mileage", &machine->currentMileage, 0, 1000000); break;
        case 8:  inputIntWithValidation("Enter Next Service Mileage", &machine->nextServiceMileage, machine->currentMileage, INT_MAX); break;
        case 9:  inputStringWithValidation("Enter Owner Name", machine->ownerName, 2, 100); break;
        case 10: inputEmailWithValidation(machine->ownerEmail); break;
        case 11: inputPhoneWithValidation(machine->ownerPhone); break;
        case 12:
            inputIntWithValidation(
                "Enter Machine Type (1-TRACTOR, 2-EXCAVATOR, 3-ROLLER, 4-CRANE, 5-MIXER)",
                (int*)&machine->machineType, 1, 5);
            break;
        case 13:
            inputIntWithValidation(
                "Enter Breakdown Frequency (1-NEVER, 2-LESS_THAN_THREE, 3-LESS_THAN_FIVE, 4-MORE_THAN_FIVE)",
                (int*)&machine->breakdowns, 1, 4);
            break;

        case -1: printf("Exit...\n"); return NULL;

        case 0:
            validationRes = validateMachine(machine);
            printf("%s\n", getValidationError(validationRes));

            if (validationRes != VALIDATION_OK) {
                choice = -2;
            }

            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return nodeToEdit;
}

void inputPath(char* buffer, int size, const char* prompt) {
    clearInput();

    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    else {
        buffer[0] = '\0';
    }
}

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

