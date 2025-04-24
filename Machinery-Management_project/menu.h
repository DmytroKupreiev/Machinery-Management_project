#include "types.h"

void runApp(MachineDBNode* dataBase, User* users);
int  runLogin(User* users);

void addMachine(MachineDBNode** head);
void deleteMachine(MachineDBNode** head);
void updateMachine(MachineDBNode** head);
void generateReportFile(MachineDBNode* head);