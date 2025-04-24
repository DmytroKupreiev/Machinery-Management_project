#include "view.h"
#include "user_input.h"
#include "machinery_db.h"
#include "login.h"

#include "menu.h"

#include <stdlib.h>
#include <string.h>

void writeReportFile(MachineDBNode* head, const char* filename);

void runApp(MachineDBNode* dataBase, User* users)
{
    int access = runLogin(users);

    if (!access) {
        printf("Access denied. Exiting...\n");
        return;
    }

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
        case 7: generateReportFile(dataBase); break;
        case 8: displaySortDB(dataBase); break;
        case 9: system("cls"); break;
        case 0: printf("Saving data and exiting...\n"); break;
        default:printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    saveToFile(dataBase, DB_PATH);
}

int runLogin(User* users)
{
    char username[MAX_STRING];
    char password[CREDENTIALS_LEN];
    int attempts = 3;

    while (attempts > 0) {
        printf("\n=== Login System ===\n");
        printf("Username: ");
        if (fgets(username, MAX_STRING, stdin) == NULL) {
            clearInput();
            continue;
        }
        username[strcspn(username, "\n")] = '\0';

        printf("Password: ");
        getHiddenPassword(password);

        if (authenticate(users, username, password)) {
            printf("\nWelcome, %s!\n", username);
            return 1;
        }

        printf("\nInvalid credentials. Attempts left: %d\n", --attempts);
    }
    return 0;
}

void addMachine(MachineDBNode** head)
{
    MachineDBNode* newNode = inputMachineData(head, NULL);

    if (newNode != NULL) {
        *head = addRowByKey(*head, newNode);
    }
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
        
        inputMachineData(head, findNode);
    } while (1);

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
    } while (1);

}

void generateReportFile(MachineDBNode* head) {
    char filename[256];
    inputPath(filename, sizeof(filename), "Enter report file path (default: report.txt): ");

    if (strlen(filename) == 0) {
        strcpy(filename, "report.txt");
    }

    writeReportFile(head, filename);
}

void writeReportFile(MachineDBNode* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }

    printBreakdownStatistics(file, head);
    printTableHeader(file, "ALL MACHINES");

    MachineDBNode* current = head;
    while (current != NULL) {
        printDBNode(file, current);
        current = current->next;
    }

    fclose(file);
    printf("Report successfully generated to %s\n", filename);
}