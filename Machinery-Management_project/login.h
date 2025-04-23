#pragma once

#include "constants.h"

typedef struct {
    char username[MAX_STRING];
    char password[CREDENTIALS_LEN];
} User;

int login_system(User* users);
int authenticate(User* users, const char* username, const char* password);
void get_hidden_password(char* buffer);
User* init_login_system(const char* path);
