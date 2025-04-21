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
MachineDBNode* addRowByValuation(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* deleteRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* findRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* sortByValuation(MachineDBNode* head);

void calculateBreakdownStats(MachineDBNode* head, int stats[5]);
MachineDBNode* getLast(MachineDBNode* head);
int getLenght(MachineDBNode* head);

MachineDBNode* initializeFromFile(const char* filePath);
void saveToFile(MachineDBNode* head, const char* path);