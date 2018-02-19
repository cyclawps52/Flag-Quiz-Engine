#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../custom/custom.h"
#include "auth.h"

int checkIfFirstRun()
{
	FILE* defTeacher;
	defTeacher = fopen("teachers/default.teacher", "rb");
	if(defTeacher == NULL)
	{
		//Give info
		printf("No teacher account found!\n");
		printf("Press ENTER to create a teacher account.\n");
		fflush(stdin);
		getchar();

		//Create first teacher user
		firstRunTeacher();
	}

	fclose(defTeacher);
	return 0;
}

int firstRunTeacher()
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

    //write password to file
    fwrite(password, sizeof(char), 50, newUser);
    
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
		return 1;
	}
	fwrite("abc123", sizeof(char), 6, teacherFile);
	fclose(teacherFile);  

	//create teachers/default.teacher file
	teacherFile = fopen("teachers/default.teacher", "wb");
	if(teacherFile==NULL)
	{
		printf("There was an error creating the default teacher file.\n");
		pete();
		return 1;
	}
	fwrite("abc123", sizeof(char), 6, teacherFile);
	fclose(teacherFile); 

	fclose(newUser);
	return 0;
}

//returns permission value of login
int login(char carryID[])
{
	clear();

	//Get user ID
	char userID[100];
	printf("Username: ");
	fflush(stdin);
	fgets(userID, 100, stdin);
	char userIDLen = strlen(userID);
	userID[userIDLen-1] = '\0';
	strcpy(carryID, userID);

	//check if userID exists
	char userIDPath[150] = "users/";
	strcat(userIDPath, userID);
	strcat(userIDPath, ".user");
	FILE* checkUser;
	checkUser = fopen(userIDPath, "rb");
	if(checkUser == NULL)
	{
		printf("The user %s does not exist!\n", userID);
		pete();
		return -1;
	}
	fclose(checkUser);
	
	//get userID password from .user file
	char passwordBox[32];
	retrievePassword(userID, passwordBox);

	//get password from user
	char indChar;
    char password[32];
    int passLen=0, i, boCheck=0;
    clear();
    printf("Username: %s\n", userID);
    printf("Please enter the password (max 32 char): ");
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
        printf("Username: %s\n", userID);
    	printf("Please enter the password (max 32 char): ");
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

    //compare inputted password with user inputted
    if(strcmp(password, passwordBox) == 0)
    {
    	//continue
    }
    else
    {
    	printf("\nInvalid login!\n");
    	pete();
    	return -1;
    }

    //check if user is a teacher
    int checkVal = checkTeacher(userID);
    if(checkVal == 1)
    {
    	return 1;
    }

	return 0;
}

//prompts for addUser
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

    //write password to file
    fwrite(password, sizeof(char), 50, newUser);

    //promote teacher if chosen
    int promoteUser;
    printf("\nWill this user be for a teacher?\n");
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
			return 1;
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

	fclose(userFile);
	return 0;
}

//asks for user and displays password
int retrievePasswordManual()
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

	printf("The password for %s is: %s\n", userID, passwordBox);
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
		return 0;
	}

	fclose(teacherUser);
	fclose(basicUser);

	return 1;
}