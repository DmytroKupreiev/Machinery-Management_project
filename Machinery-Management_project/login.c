#include <stdio.h>
#include <string.h>
#include <conio.h> 
#include "login.h"
#include <stdlib.h>

#include "user_input.h"

User* init_login_system(const char* path) {
    User* users = (User*)malloc(MAX_USERS * sizeof(User));
    if (!users) {
        perror("Memory allocation failed");
        return NULL;
    }

    FILE* file = fopen(path, "r");
    if (!file) {
        free(users);
        perror("Failed to open login file");
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

int authenticate(User* users, const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return 1; 
        }
    }
    return 0;
}

void get_hidden_password(char* buffer) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); 

        if (ch == '\r' || ch == '\n') { 
            buffer[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        }
        else if (i < CREDENTIALS_LEN - 1) {
            buffer[i++] = ch;
            printf("*");
        }
    }
}

int login_system(User* users)
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
        get_hidden_password(password);

        if (authenticate(users, username, password)) {
            printf("\nWelcome, %s!\n", username);
            return 1;
        }

        printf("\nInvalid credentials. Attempts left: %d\n", --attempts);
    }
    return 0;
}