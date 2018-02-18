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
	int menu;
	
	while(1)
	{
		clear();
		//PUSHED FEATURES
		printf("1. Make Quiz\n");
		printf("2. Take Quiz\n");
		printf("3. Grade Quiz\n");

		//IN PROGRESS
		printf("4. Add User\n");
		printf("5. Retrieve Password Interface\n");

		//DEBUG
		

		//DEFAULTS
		printf("0. Quit Program\n");
		printf("\t\tChoice: ");
		fflush(stdin);
		if(scanf("%d", &menu) == 0)
		{
			printf("Invalid choice, press enter to retry.\n");
			fflush(stdin);
			getchar();
			fflush(stdin);
			menu = 1337;
		}

		switch(menu)
		{
			//PUSHED FEATURES
			case 1:
				maker();
				break;
			case 2:
				takeQuiz();
				break;
			case 3:
				grader();
				break;

			//IN PROGRESS
			case 4:
				addUser();
				break;
			case 5:
				retrievePassword2();
				break;

			//DEBUG
			

			//DEFAULTS
			case 0:
				return 0;
				break;
			case 1337:
				break;
			default:
				printf("Invalid choice, press enter to retry.\n");
				fflush(stdin);
				getchar();
		}
	}
	
	return 0;
}