#pragma once

#include "machinery_db.h"
#include <stdio.h>

void displayMenu();
void displayDBNode(MachineDBNode* row);
void displayAllMachines(MachineDBNode* head, const char* header);
void displayMachineByKey(MachineDBNode* head);
void displaySortDB(MachineDBNode* head);
void displayBreakdownStatistics(MachineDBNode* head);
void displayTableHeader(const char* label);

void printBreakdownStatistics(FILE* output, MachineDBNode* head);
void printDBNode(FILE* output, MachineDBNode* row);
void printTableHeader(FILE* output, const char* label);
void printRepeated(FILE* stream, char ch, int count);