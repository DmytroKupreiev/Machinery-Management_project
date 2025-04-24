#pragma once

#include "machinery_db.h"

void clearInput(void);
int  isValidEmail(const char* email);
int  isValidPhone(const char* phone);
int  isChassisNumberUnique(MachineDBNode* head, const char* chassisNumber);

void inputPath(char* buffer, int size, const char* prompt);
void inputStringWithValidation(const char* prompt, char* dest, int minLen, int maxLen);
void inputIntWithValidation(const char* prompt, int* dest, int minVal, int maxVal);
void inputFloatWithValidation(const char* prompt, float* dest, float minVal, float maxVal);
void inputEmailWithValidation(char* email);
void inputPhoneWithValidation(char* phone);
void inputChassisNumber(MachineDBNode* head, char* chassisNumber);
MachineDBNode* inputMachineData(MachineDBNode** head, MachineDBNode* node);