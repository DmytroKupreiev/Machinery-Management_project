#include <stdio.h> 
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#include "user_input.h"

int isValidEmail(const char* email) {
    int atCount = 0, dotCount = 0;
    for (int i = 0; email[i] != '\0'; i++) {
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
        scanf("%d", dest);
        clearInput();
    } while (*dest < minVal || *dest > maxVal);
}

void inputFloatWithValidation(const char* prompt, float* dest, float minVal, float maxVal) {
    do {
        printf("%s (%.2f-%.2f): ", prompt, minVal, maxVal);
        scanf("%f", dest);
        clearInput();
    } while (*dest < minVal || *dest > maxVal);
}

void inputEmailWithValidation(char* email) {
    do {
        printf("Enter Owner Email: ");
        fgets(email, MAX_STRING, stdin);
        email[strcspn(email, "\n")] = '\0';

        if (!isValidEmail(email)) {
            printf("Invalid email format! Must contain @ and .\n");
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

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}