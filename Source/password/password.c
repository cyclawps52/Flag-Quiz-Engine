#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../custom/custom.h"
#include "password.h"

int password()
{
	clear();

	FILE* fp;
	fp = fopen("password.bin", "w+b");
	if(fp == NULL)
	{
		printf("Shit got broken, PETE.\n");
		fflush(stdin);
		getchar();
		return 1;
	}	

	char password[100];
	printf("Enter a password: ");
	fflush(stdin);
	fgets(password, 100, stdin);
	int passwordLen = strlen(password);
	password[passwordLen-1] = '\0';

	printf("password=%s\n", password);
	passwordLen = strlen(password);

	fwrite(password, sizeof(char), passwordLen, fp);

	char password2[100];
	fseek(fp, 0, SEEK_SET);
	int password2Len = fread(password2, sizeof(char), 100, fp);
	password2[password2Len] = '\0';

	line();
	printf("password2=%s\n", password2);
	printf("password2Len=%d\n", password2Len);
	line();

	printf("PETE\n");
	fflush(stdin);
	getchar();

	return 0;
}

//users cannot change password, teacher mode option to delete user file
