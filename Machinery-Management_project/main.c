#include <stdio.h>

#include "view.h"
#include "login.h"

void main()
{	
	User* users = init_login_system("users.txt");
	MachineDBNode* db = initializeFromFile(DB_PATH);
	runViewApp(db, users);
}