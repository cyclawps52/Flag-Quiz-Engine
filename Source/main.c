//STANDARD
#include <stdio.h>

//PUSHED FEATURES
#include "custom/custom.h"
#include "grader/grader.h"
#include "maker/maker.h"
#include "takeQuiz/takeQuiz.h"

//DEBUG
#include "password/password.h"

int main()
{
	int menu;
	
	while(1)
	{
		clear();
		printf("1. Make Quiz\n");
		printf("2. Take Quiz\n");
		printf("3. Grade Quiz\n");
		printf("4: DEBUG: Password\n");
		printf("0. Quit Program\n");
		printf("\t\tChoice: ");
		fflush(stdin);
		if(scanf("%d", &menu) == 0)
		{
			printf("Invalid choice, press enter to retry.\n");
			fflush(stdin);
			getchar();
			fflush(stdin);
			menu = -1;
		}

		switch(menu)
		{
			case 1:
				maker();
				break;
			case 2:
				takeQuiz();
				break;
			case 3:
				grader();
				break;
			case 4:
				password();
				break;
			case 0:
				return 0;
				break;
			case -1:
				break;
			default:
				printf("Invalid choice, press enter to retry.\n");
				fflush(stdin);
				getchar();
		}
	}
	

	return 0;
}