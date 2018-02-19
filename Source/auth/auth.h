#ifndef AUTH_H
#define AUTH_H

int checkIfFirstRun();
int firstRunTeacher();

int login(char carryID[]);

int addUser();

int retrievePassword();
int retrievePasswordManual();

int checkTeacher();

#endif