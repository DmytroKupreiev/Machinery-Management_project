#pragma once

#include "types.h"

int authenticate(User* users, const char* username, const char* password);
void getHiddenPassword(char* buffer);
User* loadLoginFile(const char* path);
void freeUsers(User* users);