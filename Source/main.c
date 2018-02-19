//STANDARD
#include <stdio.h>
#include <stdlib.h>

//PUSHED FEATURES
#include "custom/custom.h"
#include "grader/grader.h"
#include "maker/maker.h"
#include "takeQuiz/takeQuiz.h"

//IN PROGRESS
#include "auth/auth.h"

//DEBUG


//MAIN
int main()
{
	setbuf(stdout, NULL);
	int menu;

	int permissionLevel = -1;

	clear();
	checkIfFirstRun();
	
	while(1)
	{
		clear();
		int menuChoice;

		if(permissionLevel == -1)
		{
			printf("1. Login\n");
			printf("0. Exit Program\n");
			if(scanf("%d", &menuChoice) == 0)
			{
				printf("Invalid option!\n");
				printf("Press ENTER to retry.\n");
				menuChoice = 1337;
				fflush(stdin);
				getchar();
			}
			switch(menuChoice)
			{
				case 1:
					permissionLevel = login();
					break;
				case 0:
					return 0;
				default:
					printf("Invalid option!\n");
					printf("Press ENTER to retry.\n");
					fflush(stdin);
					getchar();
			}
		}
		else if(permissionLevel == 0)
		{
			printf("1. Take Quiz\n");
			printf("2. Check Grade (not implemented yet)\n");
			printf("0. Logout\n");
			if(scanf("%d", &menuChoice) == 0)
			{
				printf("Invalid option!\n");
				printf("Press ENTER to retry.\n");
				menuChoice = 1337;
				fflush(stdin);
				getchar();
			}

			switch(menuChoice)
			{
				case 1:
					takeQuiz();
					break;
				case 2:
					//checkGrade will go here
					break;
				case 0:
					permissionLevel = -1;
					break;
				case 1337:
					break;
				default:
					printf("Invalid option!\n");
					printf("Press ENTER to retry.\n");
					fflush(stdin);
					getchar();
			}
		}
		else if(permissionLevel == 1)
		{
			printf("1. Create Quiz\n");
			printf("2. Grade Quiz\n");
			printf("3. Create User\n");
			printf("4. Retrieve User Password\n");
			printf("0. Logout\n");
			if(scanf("%d", &menuChoice) == 0)
			{
				printf("Invalid option!\n");
				printf("Press ENTER to retry.\n");
				menuChoice = 1337;
				fflush(stdin);
				getchar();
			}

			switch(menuChoice)
			{
				case 1:
					maker();
					break;
				case 2:
					grader();
					break;
				case 3:
					addUser();
					break;
				case 4:
					retrievePasswordManual();
					break;
				case 0:
					permissionLevel = -1;
					break;
				case 1337:
					break;
				default:
					printf("Invalid option!\n");
					printf("Press ENTER to retry.\n");
					fflush(stdin);
					getchar();
			}
		}
	}
	
	return 0;
}