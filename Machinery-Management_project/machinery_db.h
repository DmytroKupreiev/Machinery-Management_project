#pragma once

#include "types.h"

MachineDBNode* createRow();
MachineDBNode* copyNode(const MachineDBNode* source);
MachineDBNode* addRow(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* addRowByKey(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* addRowByValuation(MachineDBNode* head, MachineDBNode* newNode);
MachineDBNode* deleteRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* findRowByKey(MachineDBNode* head, const char* key);
MachineDBNode* sortByValuation(MachineDBNode* head);

MachineDBNode* getLast(MachineDBNode* head);
int			   getLength(MachineDBNode* head);

MachineDBNode* loadDatabaseFile(const char* filePath);
void		   saveToFile(MachineDBNode* head, const char* path);

void calculateBreakdownStats(MachineDBNode* head, float stats[5], int rowCount);