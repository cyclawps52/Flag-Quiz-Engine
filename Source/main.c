#include <stdio.h>

#include "custom/custom.h"
#include "grader/grader.h"
#include "maker/maker.h"
#include "takeQuiz/takeQuiz.h"
#include "dumpTest/dumpTest.h"

int main()
{
	int menu;
	
	while(1)
	{
		clear();
		printf("1. Make Quiz\n");
		printf("2. Take Quiz\n");
		printf("3. Grade Quiz\n");
		printf("4. DEBUG: DUMP TEST\n");
		printf("\t\tChoice: ");
		fflush(stdin);
		scanf("%d", &menu);

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
				dumpTest();
				break;
		}
	}
	

	return 0;
}