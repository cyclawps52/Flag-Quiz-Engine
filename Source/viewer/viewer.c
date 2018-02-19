#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "viewer.h"
#include "../custom/custom.h"

int gradeViewer(char carryID[])
{
	FILE* gradeFile;
	FILE* testFile;
	FILE* resultsFile;

	//get quizID
	printf("What quiz do you want to check the grade for(100 char max): ");
	fflush(stdin);
	char testID[100];
	fgets(testID, 100, stdin);
	strtok(testID, "\n");

	//check if quiz is valid
	char testFilePath[150] = "quizes/";
	strcat(testFilePath, testID);
	strcat(testFilePath, ".quizfile");
	testFile = fopen(testFilePath, "r");
	if(testFile == NULL)
	{
		printf("Quiz %s does not exist!\n", testID);
		pete();
		return 1;
	}

	//check if student has taken quiz
	char resultsFilePath[300] = "results/";
	strcat(resultsFilePath, testID);
	strcat(resultsFilePath, "/");
	strcat(resultsFilePath, carryID);
	strcat(resultsFilePath, ".quizresults");
	resultsFile = fopen(resultsFilePath, "r");
	if(resultsFile == NULL)
	{
		printf("You have not taken %s yet!\n", testID);
		pete();
		return 1;
	}


	//get string for gradeFile
	char gradeFilePath[150] = "grades/";
	strcat(gradeFilePath, testID);
	strcat(gradeFilePath, "/");
	strcat(gradeFilePath, carryID);
	strcat(gradeFilePath, ".grade");

	//check if grade file exists
	gradeFile = fopen(gradeFilePath, "r");
	if(gradeFile == NULL)
	{
		printf("Grades have not been released for %s yet!\n", testID);
		pete();
		return 1;
	}

	//display grade file
	clear();
	char c = fgetc(gradeFile);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(gradeFile);
    }

    line();
    pete();
    fclose(resultsFile);
	fclose(gradeFile);
	fclose(testFile);
	return 0;
}

int testViewer(char carryID[])
{

	return 0;
}