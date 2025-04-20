#pragma once

#include <stdbool.h>
#include "machine.h"

struct MachineDBNode;

typedef struct MachineDBNode {
	Machine data;
	struct MachineDBNode* next;
} MachineDBNode;

MachineDBNode* createRow();
MachineDBNode* addRow(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* addRowByKey(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* deleteRowByKey(MachineDBNode* head, const char*);
MachineDBNode* findRowByKey(MachineDBNode* head, const char*);
MachineDBNode* getLast(MachineDBNode* head);

MachineDBNode* initializeFromFile(char*);
void saveToFile(MachineDBNode* head, const char* path);