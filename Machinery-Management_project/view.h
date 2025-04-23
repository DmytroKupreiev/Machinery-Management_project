#pragma once

#include "machinery_db.h"
#include "login.h"

void runViewApp(MachineDBNode* dataBase, User* users);

MachineDBNode* constructMachine(MachineDBNode** head, MachineDBNode* node);
void addMachine(MachineDBNode** head);
void deleteMachine(MachineDBNode** head);
void updateMachine(MachineDBNode** head);
void displayDBNode(MachineDBNode* row);
void displayAllMachines(MachineDBNode* head, const char* header);
void displayMachineByKey(MachineDBNode* head);
void displaySortDB(MachineDBNode* head);
void displayBreakdownStatistics(MachineDBNode* head);
void displayTableHeader(const char* label);

void generateReportFile(MachineDBNode* head, const char* filename);
void printBreakdownStatistics(FILE* output, MachineDBNode* head);
void printDBNode(FILE* output, MachineDBNode* row);
void printTableHeader(FILE* output, const char* label);