#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> 
#include <string.h>
#include <stdbool.h>

#include "machinery_db.h"

MachineDBNode* createRow()
{
	MachineDBNode* newNode = (MachineDBNode*)malloc(sizeof(MachineDBNode));
	if (newNode == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	Machine* machine = &(newNode->data);
	
	// zeroing out new node data
	memset(machine, 0, sizeof(Machine));
	machine->currentValuation = -1;
	machine->cost = -1;
	machine->yearOfManufacture = -1;
	machine->currentMileage = -1;
	machine->nextServiceMileage = -1;
	newNode->next = NULL;

	return newNode;
}

MachineDBNode* copyNode(const MachineDBNode* source) {
	if (source == NULL) return NULL;

	MachineDBNode* newNode = createRow();

	// copy node using copy inner data
	newNode->data = source->data; 
	newNode->next = NULL;

	return newNode;
}

MachineDBNode* getLast(MachineDBNode* head) 
{
	if (head == NULL) { return head; }

	MachineDBNode* current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	return current;
}

MachineDBNode* addRow(MachineDBNode* head, MachineDBNode* newNode)
{
	if (head == NULL) {
		newNode->next = NULL;
		head = newNode;
	}
	else {
		MachineDBNode* current = head;

		while (current->next != NULL) {
			current = current->next;
		}

		newNode->next = NULL;
		current->next = newNode;
	}

	return head;
}

MachineDBNode* addRowByKey(MachineDBNode* head, MachineDBNode* newNode)
{
	if (head == NULL || strcmp(newNode->data.chassisNumber, head->data.chassisNumber) < 0) {
		newNode->next = head;
		return newNode;
	}

	MachineDBNode* current = head;

	while (current->next != NULL &&
		   strcmp(newNode->data.chassisNumber, current->next->data.chassisNumber) > 0) //Lexicographic comparison => "13 > 123"
	{
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;

	return head;
}

MachineDBNode* addRowByValuation(MachineDBNode* head, MachineDBNode* newNode) {
	if (head == NULL || newNode->data.currentValuation <= head->data.currentValuation) {
		newNode->next = head;
		return newNode;
	}

	MachineDBNode* current = head;

	while (current->next != NULL &&
		newNode->data.currentValuation > current->next->data.currentValuation) {
		current = current->next;
	}

	newNode->next = current->next;
	current->next = newNode;

	return head;
}

MachineDBNode* deleteRowByKey(MachineDBNode* head, const char* key)
{
	if (head == NULL) {
		return head;
	}

	MachineDBNode* current = head;
	MachineDBNode* previous = NULL;

	while (current != NULL) {

		if (strcmp(current->data.chassisNumber, key) == 0) {
			if (previous == NULL) {
				head = current->next;
			}
			else {
				previous->next = current->next;
			}

			free(current);
			return head;
		}

		previous = current;
		current = current->next;
	}

	return head;
}

MachineDBNode* findRowByKey(MachineDBNode* head, const char* key) {
	MachineDBNode* current = head;

	while (current != NULL) {
		if (strcmp(current->data.chassisNumber, key) == 0) {
			return current;
		}

		current = current->next;
	}

	return NULL;
}

MachineDBNode* loadDatabaseFile(const char* filePath)
{
	FILE* db_file = fopen(filePath, "r");

	if (db_file == NULL) {
		printf("DB file open error\n");
		return NULL;
	}

	MachineDBNode* head = NULL;

	while (!feof(db_file)) {

		MachineDBNode* newItem = createRow();

		if (fscanf(db_file, "%s %s %s %d %f %f %d %d %s %s %s %d %d",
			newItem->data.chassisNumber, newItem->data.make, newItem->data.model,
			&newItem->data.yearOfManufacture, &newItem->data.cost, &newItem->data.currentValuation,
			&newItem->data.currentMileage, &newItem->data.nextServiceMileage,
			newItem->data.ownerName, newItem->data.ownerEmail, newItem->data.ownerPhone,
			(int*)&newItem->data.machineType, (int*)&newItem->data.breakdowns) != 13) {

			free(newItem);
			break;
		}

		head = addRow(head, newItem);
	}

	fclose(db_file);
	return head;
}

void freeDB(MachineDBNode** head) {
	if (head == NULL || *head == NULL) {
		return;
	}

	MachineDBNode* current = *head;
	MachineDBNode* next = NULL;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	*head = NULL;
}

void saveToFile(MachineDBNode* head, const char* filePath)
{
	FILE* db_file = fopen(filePath, "w");

	if (db_file == NULL) {
		printf("Error opening file for writing\n");
		return;
	}

	MachineDBNode* current = head;

	while (current != NULL) {
		fprintf(db_file, "%s %s %s %d %.2f %.2f %d %d %s %s %s %d %d\n",
			current->data.chassisNumber,
			current->data.make,
			current->data.model,
			current->data.yearOfManufacture,
			current->data.cost,
			current->data.currentValuation,
			current->data.currentMileage,
			current->data.nextServiceMileage,
			current->data.ownerName,
			current->data.ownerEmail,
			current->data.ownerPhone,
			current->data.machineType,
			current->data.breakdowns);

		current = current->next;
	}

	fclose(db_file);
}

int getLength(MachineDBNode* head)
{
	MachineDBNode* current = head;
	int counter = 0;

	while (current != NULL) {
		counter++;
		current = current->next;
	}

	return counter;
}

int getAllWithBreakdowns(MachineDBNode* head)
{
	MachineDBNode* current = head;
	int counter = 0;

	while (current != NULL) {
		// Check if breakdown value is within valid enum range
		if (current->data.breakdowns >= NEVER 
			&& current->data.breakdowns <= MORE_THAN_FIVE)
		{
			counter++;
		}

		current = current->next;
	}

	return counter;
}

MachineDBNode* sortByValuation(MachineDBNode* head) {
	MachineDBNode* sorted = NULL;
	MachineDBNode* current = head;

	//Sorting by recreating the list
	while (current != NULL) {
		MachineDBNode* next = current->next;
		MachineDBNode* newNode = copyNode(current);

		sorted = addRowByValuation(sorted, newNode);
		current = next;
	}

	return sorted;
}

void calculateBreakdownStats(MachineDBNode* head, float stats[5], int rowCount) {
	// stats[0] - *not use*
	// stats[1] - NEVER
	// stats[2] - LESS_THAN_THREE
	// stats[3] - LESS_THAN_FIVE
	// stats[4] - MORE_THAN_FIVE

	MachineDBNode* current = head;
	while (current != NULL) {
		BreakdownFreq freq = current->data.breakdowns;
		if (freq >= NEVER && freq <= MORE_THAN_FIVE) {
			stats[freq]++;
		}
		current = current->next;
	}

	stats[NEVER]           = (float)stats[NEVER]           / rowCount * 100;
	stats[LESS_THAN_THREE] = (float)stats[LESS_THAN_THREE] / rowCount * 100;
	stats[LESS_THAN_FIVE]  = (float)stats[LESS_THAN_FIVE]  / rowCount * 100;
	stats[MORE_THAN_FIVE]  = (float)stats[MORE_THAN_FIVE]  / rowCount * 100;
}

