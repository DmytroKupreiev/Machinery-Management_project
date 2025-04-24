#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "login.h"
#include "user_input.h"

User* loadLoginFile(const char* path) {
    User* users = (User*)malloc(MAX_USERS * sizeof(User));

    if (!users) {
        printf("Memory allocation failed");
        return NULL;
    }

    FILE* file = fopen(path, "r");
    if (!file) {
        free(users);
        printf("Failed to open login file");
        return NULL;
    }

    for (int i = 0; i < MAX_USERS; i++) {
        if (fscanf(file, "%99s %6s", users[i].username, users[i].password) != 2) {
            free(users);
            fclose(file);
            fprintf(stderr, "Error: Login file must contain exactly %d records\n", MAX_USERS);
            return NULL;
        }
    }

    fclose(file);
    return users;
}

void freeUsers(User* users) {
    if (users != NULL) {
        free(users);
    }
}

int authenticate(User* users, const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return 1; 
        }
    }
    return 0;
}

void getHiddenPassword(char* buffer) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); // Reads character without echo

        if (ch == '\r' || ch == '\n') { 
            buffer[i] = '\0';
            printf("\n");
            break;
        }
        // Handle Backspace
        else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        }
        // Handle regular characters
        else if (i < CREDENTIALS_LEN - 1) { 
            buffer[i++] = ch;
            printf("*");
        }
    }
}
