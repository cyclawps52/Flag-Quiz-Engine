#ifndef DELETE_H
#define DELETE_H

int teacherDelete(char carryID[]);

int remove_directory(const char *path);

int removeDump();
int removeResults();
int removeGrades();

int softDelete();
int hardDelete();

int factoryReset();

#endif