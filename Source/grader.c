#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void line()
{
    printf("----------------------------------\n");
}

void make_directory(const char* name) 
{
    #if defined __linux__ || defined(__unix__) || defined(__APPLE__)
        mkdir(name, 777); 
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        _mkdir(name);
    #endif
}

int main()
{
	//variables used for directory reading
	DIR* FD;
    struct dirent* in_file;
    FILE* master_results;
    FILE* current_file;
    char buffer[250];
    FILE* quiz;

    //track number of student files ran through
    int numStudents=0;

    //get name of quiz to run
    char quizName[140]="quizes/";
    char temp[100];
    printf("What quiz do you want to grade(100 char max): ");
    scanf("%s", temp);
    line();
    strcat(quizName, temp);

    //add .quizfile extension to string
    strcat(quizName, ".quizfile");

    //opening quiz file stream r with binary
    quiz = fopen(quizName, "r+b");
    if(quiz==NULL)
    {
        printf("There was an error opening the quiz file.\n");
        printf("Press ENTER to close Grader.\n");
        fflush(stdin);
        getchar();
        return 1;
    }

    //get number of questions in quiz
    int numQs;
    char buffer2[225];
    fseek(quiz, 3, SEEK_SET);
    fgets(buffer2, 225, quiz);
    numQs = atoi(buffer2);

    //create array to store question statistics and fill with 0s
    float questionStats[4][numQs+1];
    int i, j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<numQs+1;j++)
        {
            questionStats[i][j]=0;
        }
    }

	//create a grades/quizname/overall.grade file to store calculations
    char gradeFile[300]="grades/";
    strcat(gradeFile, temp);
    strcat(gradeFile, "/");
    make_directory(gradeFile);
    strcat(gradeFile, "overall.grade");
    master_results = fopen(gradeFile, "w");
    if (master_results == NULL)
    {
        fprintf(stderr, "Error: Failed to create %s\n", gradeFile);
        printf("Press ENTER to close Grader.\n");
        fflush(stdin);
        getchar();
        return 1;
    }

    //creating string for results directory
    char resultsDir[300]="results/";
    strcat(resultsDir, temp);
    strcat(resultsDir, "/");

    //checking if results-quizname/ directory can open and opening if it exists
    if (NULL == (FD = opendir (resultsDir))) 
    {
        printf("Error: Failed to open %s directory\n", resultsDir);
        printf("This error is common if no one has taken the selected quiz yet.\n");
        printf("Press ENTER to close Grader.\n");
        fflush(stdin);
        getchar();
        fclose(master_results);
        return 1;
    }

    //looping through all files in results/ directory
    while ((in_file = readdir(FD))) 
    {
    	//remove parent directory listings
        if (!strcmp (in_file->d_name, "."))
        {
            continue; 
        }
        if (!strcmp (in_file->d_name, ".."))    
        {
            continue; //do not print
        }

        //get name of file with results/ dir prepended
        char fileString[150];
        strcpy(fileString, resultsDir);
        strcat(fileString, in_file->d_name);

        //open file in rb mode and check
        current_file = fopen(fileString, "r+b");
        if (current_file == NULL)
        {
            printf("Error: Failed to open file %s!\n", in_file->d_name);
            printf("Press ENTER to close Grader.\n");
            fflush(stdin);
            getchar();
            fclose(master_results);
            return 1;
        }
        else
        {
            printf("Now grading %s!\n", in_file->d_name);
        }

        //storing studentName for future use
        char studentName[150];
        strcpy(studentName, in_file->d_name);
        int studentNameLen = strlen(studentName);
        studentName[studentNameLen-12]='\0';

        //opening filestream for individual results
        char studentID[300]="grades/";
        strcat(studentID, temp);
        strcat(studentID, "/");
        strcat(studentID, in_file->d_name);
        int studentIDLen = strlen(studentID);
        studentID[studentIDLen-11] = '\0';
        strcat(studentID, "grade");
        FILE* lone_results;
        lone_results = fopen(studentID, "w+b");
        if(lone_results == NULL)
        {
            printf("Error: Failed to create %s\n", studentID);
            printf("Press ENTER to close Grader.\n");
            fflush(stdin);
            getchar();
            fclose(lone_results);
            fclose(master_results);
            return 1;
        }
        

        //trim B: line off
        int cPos = ftell(current_file);
        fgets(buffer, 250, current_file);

        //declaring persistent counter variables
        int studentCorrect=0;
        float studentAverage=0;

        //loop through entire file and print to screen
        while (fgets(buffer, 250, current_file) != NULL)
        {
            //get question number
            if (strstr(buffer, "Q: ") != NULL)
            {
                cPos = ftell(current_file);
                fseek(current_file, cPos-3, SEEK_SET);
                int questionNum = atoi(fgets(buffer, 225, current_file));
                cPos = ftell(current_file);

                //put question number into table
                questionStats[0][questionNum] = questionNum;

                //see if answer was right or wrong
                fgets(buffer, 250, current_file);
                fseek(current_file, -2, SEEK_CUR);
                int questionStatus = atoi(fgets(buffer, 225, current_file));

                if(questionStatus==1)
                {
                    questionStats[1][questionNum]++;
                    studentCorrect++;
                    fprintf(lone_results, "Question %d: Correct!\n", questionNum);
                }
                else
                {
                    //get studentAns and expectedAns
                    fgets(buffer, 250, current_file);
                    fseek(current_file, -3, SEEK_CUR);
                    int studentAns = atoi(fgets(buffer, 250, current_file));
                    fgets(buffer, 250, current_file);
                    fseek(current_file, -3, SEEK_CUR);
                    int expectedAns = atoi(fgets(buffer, 250, current_file));
                    questionStats[2][questionNum]++;
                    fprintf(lone_results, "Question %d: Wrong! Expected %d but received %d\n", questionNum, expectedAns, studentAns);
                }
            }   
        }

        //print score and percent to individual file
        studentAverage = (float) studentCorrect / numQs * 100;
        fprintf(lone_results, "--------------------------------\n");
        fprintf(lone_results, "Score: %d out of %d\n", studentCorrect, numQs);
        fprintf(lone_results, "Percentage: %.2f%%\n", studentAverage);

        //print user and percent to overall file
        fprintf(master_results, "ID:%s - %d/%d - %.2f%%\n", studentName, studentCorrect, numQs, studentAverage);

	    //closing current file to move onto next one
        printf("Completed grading %s!\n", in_file->d_name);
        printf("Individual grade file saved to %s!\n", studentID);
        line();
	    fclose(current_file);
        fclose(lone_results);
        numStudents++;
    }

    //calculate question averages
    for(i=1;i<numQs+1;i++)
    {
        questionStats[3][i] = questionStats[1][i] / numStudents * 100;
    }

    //print questionStats to overall.grade
    fprintf(master_results, "--------------------\n");
    for(i=0;i<4;i++)
    {
        switch(i)
        {
            case 0: 
                printf("Question:\t");
                fprintf(master_results, "Question:\t"); 
                break;
            case 1: 
                printf("Correct :\t"); 
                fprintf(master_results, "Correct :\t"); 
                break;
            case 2: 
                printf("Wrong   :\t"); 
                fprintf(master_results, "Wrong   :\t"); 
                break;
            case 3: 
                printf("Percent :\t"); 
                fprintf(master_results, "Percent :\t"); 
                break;
        }
        for(j=1;j<numQs+1;j++)
        {
            if(i==3)
            {
                printf("%.2f%%\t", questionStats[i][j]);
                fprintf(master_results, "%.2f%%\t", questionStats[i][j]); 
            }
            else
            {
                printf("%.2f\t", questionStats[i][j]);
                fprintf(master_results, "%.2f\t", questionStats[i][j]); 
            }
        }
        printf("\n");
        fprintf(master_results, "\n"); 
    }

    //get total average
    float classAverage=0;
    for(i=1;i<=numQs;i++)
    {
    	classAverage += questionStats[3][i];
    }
    classAverage /= numQs;
    line();
    printf("Quiz average was %.2f%%.\n", classAverage);
    fprintf(master_results, "--------------------\n");
    fprintf(master_results, "Quiz average was: %.2f%%.\n", classAverage);

    line();
    printf("Overall results saved to %s!\n", gradeFile);
    printf("Press ENTER to exit Grader.\n");
    fflush(stdin);
    getchar();

    //closing streams
    fclose(master_results);
    fclose(quiz);
	return 0;
}