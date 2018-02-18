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