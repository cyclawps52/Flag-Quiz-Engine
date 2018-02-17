#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../custom/custom.h"
#include "dumpTest.h"

int dumpTest()
{
	//OPEN FILE POINTER FOR QUIZ
	FILE* quiz;
	quiz = fopen("./quizes/quiz1.quizfile", "r+");
	if(quiz==NULL)
	{
		printf("There was an error opening the quiz file.\n");
		printf("Program is exiting.\n");
		return 1;
	}

	//OPEN FILE POINTER FOR DUMP
	FILE* dump;
	dump = fopen("dumpTest/quiz1.dump", "w+");
	if(dump==NULL)
	{
		printf("There was an error opening the dump file.\n");
		printf("Program is exiting.\n");
		return 1;
	}

	//GET QUESTIONS
	int questionNum=1;
	char buffer[300];
	while(fgets(buffer, 225, quiz))
	{
		if(strstr(buffer, "Q: ") != NULL)
		{
			char *answerBuffer = buffer + 3;
			printf("Question %d: %s", questionNum, answerBuffer);
			fprintf(dump, "Question %d: %s", questionNum, answerBuffer);
			questionNum++;
		}
	}

	printf("PRESS ENTER TO CONTINUE\n");
	fflush(stdin);
	getchar();
		
	fclose(dump);
	fclose(quiz);
	return 0;
}