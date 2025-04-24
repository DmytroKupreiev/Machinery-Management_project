#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "user_input.h"
#include "view.h"

void displayAllMachines(MachineDBNode* head, const char* header)
{
    if (head == NULL) {
        printf("\nNo machines in the fleet.\n");
        return;
    }

    MachineDBNode* current = head;

    displayTableHeader(header);
    while (current != NULL) {
        displayDBNode(current);
        current = current->next;
    }
}

void displayMachineByKey(MachineDBNode* head)
{
    if (head == NULL) {
        printf("\nNo machines in the fleet.\n");
        return;
    }

    char key[MAX_STRING];
    printf("\nEnter chassis number: ");
    int retval = scanf("%99s", key);

    MachineDBNode* foundNode = findRowByKey(head, key);

    if (foundNode == NULL) {
        printf("\nRow not found!\n");
        return;
    }

    displayTableHeader("Found row");
    displayDBNode(foundNode);
}

void displaySortDB(MachineDBNode* head)
{
    MachineDBNode* sorted = sortByValuation(head);
    displayAllMachines(sorted, "SORTED DATABASE");
}

void displayMenu()
{
    printf("\n===== Machinery Management Ltd: Fleet Management System =====\n");
    printf("1) Display all machines to screen\n");
    printf("2) Display machine details\n");
    printf("3) Add machine\n");
    printf("4) Delete machine\n");
    printf("5) Update a machine's details\n");
    printf("6) Generate statistics\n");
    printf("7) Print all machine details into a report file\n");
    printf("8) List all the machinery in order of current valuation\n");
    printf("9) Clear terminal\n");
    printf("0) Exit system\n");
    printRepeated(stdout, '=', 61);
    printf("\n");
}

void displayTableHeader(const char* label)
{
    printTableHeader(stdout, label);
}

void displayDBNode(MachineDBNode* row) {
    printDBNode(stdout, row);
}

void displayBreakdownStatistics(MachineDBNode* head) {
    printBreakdownStatistics(stdout, head);
}

void printTableHeader(FILE* output, const char* label) {
    fprintf(output, "\n");
    printRepeated(output, '=', 63);
    fprintf(output, "  %-15s ", label);
    printRepeated(output, '=', 109);
    fprintf(output, "\n");

    fprintf(output, "%-15s %-15s %-15s %-6s %-10s %-10s %-8s %-13s %-10s %-20s %-25s %-15s %-12s\n",
        "Chassis No.", "Make", "Model", "Year", "Cost", "Valuation", "Mileage",
        "Next Service", "Type", "Owner Name", "Owner Email", "Owner Phone", "Breakdowns");

    printRepeated(output, '=', 190);
    fprintf(output, "\n");
}

void printDBNode(FILE* output, MachineDBNode* row) {
    fprintf(output, "%-15s %-15s %-15s %-6d %-10.2f %-10.2f %-8d %-13d %-10s %-20s %-25s %-15s %-12s\n",
        row->data.chassisNumber,
        row->data.make,
        row->data.model,
        row->data.yearOfManufacture,
        row->data.cost,
        row->data.currentValuation,
        row->data.currentMileage,
        row->data.nextServiceMileage,
        getMachineTypeString(row->data.machineType),
        row->data.ownerName,
        row->data.ownerEmail,
        row->data.ownerPhone,
        getBreakdownFreqString(row->data.breakdowns));
}

void printBreakdownStatistics(FILE* output, MachineDBNode* head) {
    int totalWithBreakdowns = getAllWithBreakdowns(head); // all nodes with breakdowns
    int total = getLength(head);

    if (total == 0) {
        fprintf(output, "No machines in database.\n");
        return;
    }

    // array for statistics of 5 elements, element 0 is not used 
    float statistic[5] = { 0, 0, 0, 0, 0 };
    calculateBreakdownStats(head, statistic, totalWithBreakdowns);

    fprintf(output, "\n");
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| Breakdown Statistics        | Percentage  |\n");
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| NEVER                       | %9.2f%%  |\n", statistic[NEVER]);
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| LESS THAN THREE             | %9.2f%%  |\n", statistic[LESS_THAN_THREE]);
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| LESS THAN FIVE              | %9.2f%%  |\n", statistic[LESS_THAN_FIVE]);
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| MORE THAN FIVE              | %9.2f%%  |\n", statistic[MORE_THAN_FIVE]);
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| Machines with breakdowns    | %9d   |\n", totalWithBreakdowns);
    fprintf(output, "+-----------------------------+-------------+\n");
    fprintf(output, "| Total                       | %9d   |\n", total);
    fprintf(output, "+-----------------------------+-------------+\n\n");
}

void printRepeated(FILE* stream, char ch, int count) {
    for (int i = 0; i < count; i++) {
        fputc(ch, stream);
    }
}