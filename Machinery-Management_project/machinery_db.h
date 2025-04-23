#pragma once

#include <stdbool.h>
#include "machine.h"

struct MachineDBNode;

typedef struct MachineDBNode {
	Machine data;
	struct MachineDBNode* next;
} MachineDBNode;

MachineDBNode* createRow();
MachineDBNode* copyNode(const MachineDBNode* source);
MachineDBNode* addRow(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* addRowByKey(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* addRowByValuation(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* deleteRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* findRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* sortByValuation(MachineDBNode* head);

void calculateBreakdownStats(MachineDBNode* head, float stats[5], int rowCount);
MachineDBNode* getLast(MachineDBNode* head);
int getLength(MachineDBNode* head);

MachineDBNode* initializeFromFile(const char* filePath);
void saveToFile(MachineDBNode* head, const char* path);