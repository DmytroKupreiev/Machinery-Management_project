#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "view.h"
#include "user_input.h"

void displayMenu();
void displayTableHeader(const char* label);
void printDBNode(MachineDBNode* row);


void runViewApp(MachineDBNode* dataBase)
{
    int choice = -1;

    do {
        displayMenu();
        printf("Enter your choice (1-9): ");
        int countValue = scanf("%d", &choice);

        if (countValue != 1) {
            printf("Invalid input.\n");
            clearInput();
            continue;
        }

        switch (choice) {
        case 1: displayAllMachines(dataBase, "ALL MACHINES"); break;
        case 2: displayMachineByKey(dataBase); break;
        case 3: addMachine(&dataBase); break;
        case 4: deleteMachine(&dataBase); break;
        case 5: updateMachine(&dataBase); break;
        case 6: displayBreakdownStatistics(dataBase); break;
        case 7: break;
        case 8: displaySortDB(dataBase); break;
        case 9: system("cls"); break;
        case 0: printf("Saving data and exiting...\n"); break;
        default:printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    saveToFile(dataBase, DB_PATH);
}

void displayAllMachines(MachineDBNode* head, const char* header)
{
    if (head == NULL) {
        printf("\nNo machines in the fleet.\n");
        return;
    }

    MachineDBNode* current = head;

    displayTableHeader(header);
    while (current != NULL) {
        printDBNode(current);
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
    printDBNode(foundNode);
}

void addMachine(MachineDBNode** head)
{
    MachineDBNode* newNode = constructMachine(head, NULL);
    *head = addRowByKey(*head, newNode);
}

void updateMachine(MachineDBNode** head)
{
    char chassisNumber[MAX_STRING];

    clearInput();
    do {
        printf("\n=== Update Database ===\n");
        printf("Enter Chassis Number(\"-\" for exit): ");
        fgets(chassisNumber, MAX_STRING, stdin);
        chassisNumber[strcspn(chassisNumber, "\n")] = '\0';

        if (strcmp(chassisNumber, "-") == 0) { return; }

        MachineDBNode* findNode = findRowByKey(*head, chassisNumber);

        if (findNode == NULL) {
            printf("Key not found!\n");
            continue;
        }

        constructMachine(head, findNode);
    } while (true);

}

void deleteMachine(MachineDBNode** head)
{
    if (*head == NULL) {
        printf("\nDatabase is empty!\n");
        return;
    }

    char chassisNumber[MAX_STRING];
    int currentLength = getLength(*head);

    clearInput();
    do
    {
        printf("\n=== Delete row ===\n");
        printf("Enter Chassis Number(\"-\" for exit): ");
        fgets(chassisNumber, MAX_STRING, stdin);
        chassisNumber[strcspn(chassisNumber, "\n")] = '\0';

        if (strcmp(chassisNumber, "-") == 0) { return; }

        *head = deleteRowByKey(*head, chassisNumber);
        int newLength = getLength(*head);

        if (currentLength == newLength) {
            printf("\n(-) Row not found\n");
        }
        else {
            printf("\n(+) Successfully deleted\n");
            currentLength = newLength;
        }
    } while (true);

}

void displaySortDB(MachineDBNode* head)
{
    MachineDBNode* sorted = sortByValuation(head);
    displayAllMachines(sorted, "SORTED DATABASE");
}

void displayBreakdownStatistics(MachineDBNode* head)
{
    int total = getLength(head);

    if (total == 0) {
        printf("No machines in database.\n");
        return;
    }

    int numberOfCases[5] = { 0, 0, 0, 0, 0 };
    calculateBreakdownStats(head, numberOfCases);

    float neverPercent =    (float)numberOfCases[NEVER]           / total * 100;
    float rarePercent =     (float)numberOfCases[LESS_THAN_THREE] / total * 100;
    float moderatePercent = (float)numberOfCases[LESS_THAN_FIVE]  / total * 100;
    float frequentPercent = (float)numberOfCases[MORE_THAN_FIVE]  / total * 100;

    printf("\n");
    printf("+-----------------------------+-------------+\n");
    printf("| Breakdown Statistics        | Percentage  |\n");
    printf("+-----------------------------+-------------+\n");
    printf("| NEVER                       | %9.2f%%  |\n", neverPercent);
    printf("+-----------------------------+-------------+\n");
    printf("| LESS THAN THREE             | %9.2f%%  |\n", rarePercent);
    printf("+-----------------------------+-------------+\n");
    printf("| LESS THAN FIVE              | %9.2f%%  |\n", moderatePercent);
    printf("+-----------------------------+-------------+\n");
    printf("| MORE THAN FIVE              | %9.2f%%  |\n", frequentPercent);
    printf("+-----------------------------+-------------+\n");
    printf("| Total machines              | %9d   |\n", total);
    printf("+-----------------------------+-------------+\n\n");
}

MachineDBNode* constructMachine(MachineDBNode** head, MachineDBNode* node)
{
    MachineDBNode* nodeToEdit;
    Machine* machine;

    if (node == NULL) {
        nodeToEdit = createRow();
        machine = &(nodeToEdit->data);
        memset(machine, 0, sizeof(Machine));
        machine->currentValuation = -1;
        machine->cost = -1;
    }
    else {
        nodeToEdit = node;
        machine = &(nodeToEdit->data);
    }

    int choice;
    do {
        printf("\n== Current values ==\n");
        printf("1. Chassis Number: %s\n", machine->chassisNumber);
        printf("2. Make: %s\n", machine->make);
        printf("3. Model: %s\n", machine->model);
        printf("4. Year of Manufacture: %d\n", machine->yearOfManufacture);
        printf("5. Cost: %.2f\n", machine->cost);
        printf("6. Current Valuation: %.2f\n", machine->currentValuation);
        printf("7. Current Mileage: %d\n", machine->currentMileage);
        printf("8. Next Service Mileage: %d\n", machine->nextServiceMileage);
        printf("9. Owner Name: %s\n", machine->ownerName);
        printf("10. Owner Email: %s\n", machine->ownerEmail);
        printf("11. Owner Phone: %s\n", machine->ownerPhone);
        printf("12. Machine Type: %d\n", machine->machineType);
        printf("13. Breakdown Frequency: %d\n", machine->breakdowns);
        printf("0. Finish and Save\n");
        printf("Enter field to edit (0 to finish): ");

        int len = scanf("%d", &choice);
        clearInput();

        switch (choice) {
        case 1:  inputChassisNumber(*head, machine->chassisNumber); break;
        case 2:  inputStringWithValidation("Enter Make", machine->make, 3, 50); break;
        case 3:  inputStringWithValidation("Enter Model", machine->model, 2, 50); break;
        case 4:  inputIntWithValidation("Enter Year of Manufacture", &machine->yearOfManufacture, 1950, 2025); break;
        case 5:  inputFloatWithValidation("Enter Cost", &machine->cost, 0, 1000000); break;
        case 6:  inputFloatWithValidation("Enter Current Valuation", &machine->currentValuation, 0, machine->cost); break;
        case 7:  inputIntWithValidation("Enter Current Mileage", &machine->currentMileage, 0, 1000000); break;
        case 8:  inputIntWithValidation("Enter Next Service Mileage", &machine->nextServiceMileage, machine->currentMileage, INT_MAX); break;
        case 9:  inputStringWithValidation("Enter Owner Name", machine->ownerName, 2, 100); break;
        case 10: inputEmailWithValidation(machine->ownerEmail); break;
        case 11: inputPhoneWithValidation(machine->ownerPhone); break;
        case 12:
            inputIntWithValidation(
                "Enter Machine Type (1-TRACTOR, 2-EXCAVATOR, 3-ROLLER, 4-CRANE, 5-MIXER)",
                (int*)&machine->machineType, 1, 5);
            break;
        case 13:
            inputIntWithValidation(
                "Enter Breakdown Frequency (1-NEVER, 2-LESS_THAN_THREE, 3-LESS_THAN_FIVE, 4-MORE_THAN_FIVE)",
                (int*)&machine->breakdowns, 1, 4);
            break;

        case 0:

            //////////////////////////////// make minimum req /////////////////////////////

            if (strlen(machine->chassisNumber) == 0) {
                printf("Error: Chassis Number is required!\n");
                choice = -1;
            }
            else if (strlen(machine->make) == 0) {
                printf("Error: Make is required!\n");
                choice = -1;
            }
            else if (machine->yearOfManufacture == 0) {
                printf("Error: Year of Manufacture is required!\n");
                choice = -1;
            }
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return nodeToEdit;
}

void printDBNode(MachineDBNode* row)
{
    printf("%-15s %-15s %-15s %-6d %-10.2f %-10.2f %-8d %-13d %-10s %-20s %-25s %-15s %-12s\n",
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
    printf("=============================================================\n");
}

void displayTableHeader(const char* label)
{
    printf("\n===============================================================  %-15s =======================================================================================================\n", label);
    printf("%-15s %-15s %-15s %-6s %-10s %-10s %-8s %-13s %-10s %-20s %-25s %-15s %-12s\n",
        "Chassis No.", "Make", "Model", "Year", "Cost", "Valuation", "Mileage",
        "Next Service", "Type", "Owner Name", "Owner Email", "Owner Phone", "Breakdowns");
    printf("========================================================================================================================================================================================\n");
}