#ifndef AUTH_H
#define AUTH_H

int checkIfFirstRun();
int firstRunTeacher();

int login(char carryID[]);

int addUser();

int retrievePassword();
int retrievePasswordManual();

int checkTeacher();

int promoteUser();
int demoteUser(char carryID[]);

int removeUser(char carryID[]);

int changeUserPassword(char carryID[]);
int changeStudentPassword(char carryID[]);

#endif