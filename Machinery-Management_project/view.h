#pragma once

#include "machinery_db.h"

void runViewApp(MachineDBNode* dataBase);

MachineDBNode* constructMachine(MachineDBNode** head, MachineDBNode* node);
void addMachine(MachineDBNode** head);
void deleteMachine(MachineDBNode** head);
void updateMachine(MachineDBNode** head);
void displayAllMachines(MachineDBNode* head, const char* header);
void displayMachineByKey(MachineDBNode* head);
void displaySortDB(MachineDBNode* head);
void displayBreakdownStatistics(MachineDBNode* head);