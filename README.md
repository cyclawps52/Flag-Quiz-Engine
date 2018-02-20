# Flag Quiz Engine

This project consists of six main components: 

 1. The quiz maker
 2. The quiz taking engine
 3. The quiz grader
 4. The viewer engine
 5. The authentication engine
 6. The deletion engine

## Quiz Maker

The quiz maker will get various input from the teacher and store it in a .quizfile to be used by the engine and grader.
Customizable features include:

 1. Quiz name
 2. Number of questions (1-99)
 3. Number of answers per question (1-99)
 4. If the quiz will display a 'flag' if the score is above a certain threshold
	 5. The flag if chosen

Quizes are limited to multiple-choice format (ie: one of the answers is correct out of the given choices).

[The source code for the quiz maker can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/maker/maker.c)

## Quiz Engine
The quiz engine runs the selected quiz. It will create a subdirectory inside the results/ folder per quiz. 

Additionally, quiztakers will enter a unique username. The engine will not allow the same username to take the same quiz over again unless the teacher goes in and deletes the user's .quizresults file.

At the end of the quiz, the user will see their total score as a straight number as well as a percentage. If the quiz contained a flag and the user met the minimum threshold, the flag will also be displayed.

[The source code for the quiz engine can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/takeQuiz/takeQuiz.c)


## Quiz Grader
The quiz grader will generate individual grade files as well as an overall file for the selected quiz. It will create a subdirectory inside the grades/ folder per quiz. 

The individual grade file will display whether the student got the question right or wrong. If wrong, the file will display what answer was expected as well as the user's inputted answer. The student grade files will also display the questions and answers so the student can recall what the quiz was.

The overall grade file will display all user IDs with their scores displayed as straight numbers as well as percentages. At the end of the file, a table will be outputted with statistics per question. This table includes how many students got the question right, wrong, and the percentage correct for each question. The file will also include the total quiz average across all students.

The grader also outputs a testDump.grade file with the questions and answers from the quiz into the testDump/ directory. This can be used if the teacher wants to read the quiz in an easier format.

[The source code for the quiz grader can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/grader/grader.c)

## Viewer Engine
The viewer engine allows students and teachers to view grade files and test dumps. This is used to elimate the need for distributing the grade files.

[The source code for the viewer engine can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/viewer/viewer.c)

## Authentication Engine
The authentication engine controls the privilege levels across the entire program. When the program is launches for the first time, it prompts for the creation of a teacher user (permission level 1). Teachers can create more users for students (permission level 0) or additional teachers.

Teachers can also retrieve student passwords in the event that the student cannot remember their password.

Teachers can also reset a student's password directly from their teacher view.

Students can also reset their own passwords from the student view.

[The source code for the authentication engine can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/auth/auth.c)

## Deletion Engine
The deletion engine allows teachers to dynamically delete quizes, results, grades, and test dumps without leaving the program inside the console.

The deletion menu also allows a teacher to factory reset the program to an Out of Box Experience (OOBE). This removes the quizes, grades, results, users, teachers, and testDump directories to only leave the executable.

One function used inside the deletion engine is not my own work (the remove_directory function). This is commented as such inside the source code.

[The source code for the deletion engine can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/delete/delete.c)