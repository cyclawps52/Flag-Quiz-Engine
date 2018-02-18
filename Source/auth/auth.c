#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../custom/custom.h"
#include "auth.h"

int addUser()
{
	clear();

	FILE* newUser;

	//Get user ID
	char userID[100];
	printf("Enter user ID (max 100 char): ");
	fflush(stdin);
	fgets(userID, 100, stdin);
	char userIDLen = strlen(userID);
	userID[userIDLen-1] = '\0';

	//attempt to make user directory
	make_directory("users");

	//create userID string
	char userPath[110] = "users/";
	strcat(userPath, userID);
	strcat(userPath, ".user");

	//check if user ID exists
	newUser = fopen(userPath, "rb");
	if(newUser != NULL)
	{
		printf("User already exists!\n");
		pete();
		fclose(newUser);
		return 1;
	}

	//create user file
	newUser = fopen(userPath, "wb");

	//get password
	char indChar;
    char password[32];
    int passLen=0, i, boCheck=0;
    clear();
    printf("Creating user: %s\n", userID);
    printf("Please enter a password (max 32 char): ");
    while (1) 
    {
        indChar = getch();
        if (indChar == 0)
        {
            return 1;
        }
        
        if (indChar != '\r' && indChar != '\n' && indChar != '\b')
        {
        	password[passLen] = indChar;
        	passLen++;
        	boCheck++;
        }

        if(indChar == '\b')
        {
        	if(passLen>0)
        	{
        		passLen--;
        	}
        	if(boCheck>0)
        	{
        		boCheck--;
        	}
        }

        clear();
        printf("Creating user: %s\n", userID);
    	printf("Please enter a password (max 32 char): ");
        for (i = 0; i < passLen; i++)
        {
            printf("*");
        }
        if (indChar == '\n' || indChar == '\r')
        {
            break;
        }
        if(boCheck>=32)
        {
        	printf("\nOverflow detected, cutting password here!\n");
        	break;
        }

    }
    password[passLen] = '\0';

    //display password
    printf("\nDEBUG: Your password is: %s\n", password);
    fwrite(password, sizeof(char), 50, newUser);

    //promote teacher if chosen
    int promoteUser;
    printf("Will this user be for a teacher?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Choice: ");
    if( scanf("%d", &promoteUser) == 0)
    {
    	printf("Invalid option, defaulting to standard user.\n");
    	promoteUser = 2;
    }

    if(promoteUser == 1)
    {
    	//create teacher directory
    	make_directory("teachers");

    	//get teacher string
    	char teacherPath[110] = "teachers/";
		strcat(teacherPath, userID);
		strcat(teacherPath, ".teacher");

		//writing teacher file
		FILE* teacherFile;
		teacherFile = fopen(teacherPath, "wb");
		if(teacherFile == NULL)
		{
			printf("There was an error creating %s.\n", teacherPath);
			pete();
		}
		fwrite("abc123", sizeof(char), 6, teacherFile);
		fclose(teacherFile);
    }

	pete();

	fclose(newUser);
	return 0;
}

//stores inputted user's password in passed-in passwordBox
int retrievePassword(char userID[], char passwordBox[])
{
	clear();

	FILE* userFile;

	char userIDLen = strlen(userID);
	userID[userIDLen-1] = '\0';

	//attempt to make user directory
	make_directory("users");

	//create userID string
	char userPath[110] = "users/";
	strcat(userPath, userID);
	strcat(userPath, ".user");

	//check to see if user does not exist
	userFile = fopen(userPath, "rb");
	if(userFile == NULL)
	{
		printf("The user %s does not exist!\n", userID);
		pete();
		return 1;
	}

	//retrieve password
	fread(passwordBox, sizeof(char), 32, userFile);
	printf("Password retrieved as %s\n", passwordBox);

	pete();
	fclose(userFile);
	return 0;
}

//asks for user and displays password
int retrievePassword2()
{
	clear();

	FILE* userFile;

	//Get user ID
	char userID[100];
	printf("Enter user ID (max 100 char): ");
	fflush(stdin);
	fgets(userID, 100, stdin);
	char userIDLen = strlen(userID);
	userID[userIDLen-1] = '\0';

	//attempt to make user directory
	make_directory("users");

	//create userID string
	char userPath[110] = "users/";
	strcat(userPath, userID);
	strcat(userPath, ".user");

	//check to see if user does not exist
	userFile = fopen(userPath, "rb");
	if(userFile == NULL)
	{
		printf("The user %s does not exist!\n", userID);
		pete();
		return 1;
	}

	//retrieve password
	char passwordBox[32];
	fread(passwordBox, sizeof(char), 32, userFile);

	printf("Password retrieved as: %s\n", passwordBox);

	pete();
	fclose(userFile);
	return 0;
}

//returns 1 if passed in user is teacher, 0 otherwise
int checkTeacher(char toCheck[])
{
	clear();

	//prepare user path
	char toCheckPath[150] = "users/";
	strcat(toCheckPath, toCheck);
	strcat(toCheckPath, ".user");

	//checking if user exists
	FILE* basicUser;
	basicUser = fopen(toCheckPath, "rb");
	if(basicUser == NULL)
	{
		printf("No user with the name %s is in the system!\n", toCheck);
		pete();
		return -1;
	}

	//check if user is teacher
	char toCheckTeach[150] = "teachers/";
	strcat(toCheckTeach, toCheck);
	strcat(toCheckTeach, ".teacher");
	FILE* teacherUser;
	teacherUser = fopen(toCheckTeach, "rb");
	if(teacherUser == NULL)
	{
		printf("%s is not a teacher!\n");
		pete();
		return 0;
	}

	fclose(teacherUser);
	fclose(basicUser);

	printf("%s is a teacher!\n", toCheck);
	pete();
	return 1;
}

//asks for user to check
int checkTeacher2()
{
	clear();

	//get user to check
	char toCheck[100];
	printf("Which user do you want to check: ");
	fflush(stdin);
	fgets(toCheck, 100, stdin);
	char toCheckLen = strlen(toCheck);
	toCheck[toCheckLen-1] = '\0';

	//prepare user path
	char toCheckPath[150] = "users/";
	strcat(toCheckPath, toCheck);
	strcat(toCheckPath, ".user");

	//checking if user exists
	FILE* basicUser;
	basicUser = fopen(toCheckPath, "rb");
	if(basicUser == NULL)
	{
		printf("No user with the name %s is in the system!\n", toCheck);
		pete();
		return -1;
	}

	//check if user is teacher
	char toCheckTeach[150] = "teachers/";
	strcat(toCheckTeach, toCheck);
	strcat(toCheckTeach, ".teacher");
	FILE* teacherUser;
	teacherUser = fopen(toCheckTeach, "rb");
	if(teacherUser == NULL)
	{
		printf("%s is not a teacher!\n", toCheck);
		pete();
		return 0;
	}

	fclose(teacherUser);
	fclose(basicUser);

	printf("%s is a teacher!\n", toCheck);
	pete();
	return 1;
}