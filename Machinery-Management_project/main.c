#include "menu.h"
#include "login.h"
#include "machinery_db.h"

void main()
{	
	User* users       = loadLoginFile(LOGIN_PATH);
	MachineDBNode* db = loadDatabaseFile(DB_PATH);

	runApp(db, users);

	freeDB(&db);
	freeUsers(users);
}