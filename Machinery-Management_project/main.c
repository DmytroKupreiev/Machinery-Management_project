#include <stdio.h>

#include "view.h"

void main()
{
	MachineDBNode* db = initializeFromFile(DB_PATH);
	runViewApp(db);
}