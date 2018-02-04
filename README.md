# Flag Quiz Engine

This project consists of three main parts: 

 1. The quiz maker
 2. The quiz taking engine
 3. The quiz grader
 
Precompiled Windows and Linux/UNIX folders are available to download.


## Quiz Maker

The quiz maker will get various input from the 'teacher' and store it in a .quizfile (binary file) to be used by the engine and grader.
Customizable features include:

 1. Quiz name
 2. Number of questions (1-99)
 3. Number of answers per question (1-99)
 4. If the quiz will display a 'flag' if the score is above a certain threshold
	 5. The flag if chosen

Quizes are limited to multiple-choice format (ie: one of the answers is correct out of the given choices).

[The source code for the quiz maker can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/maker.c)

## Quiz Engine
The quiz engine runs the selected quiz. It will create a subdirectory inside the results/ folder per quiz. 

The netcat scripts will start a listener on port 7849 (QUIZ in T9 keyboard) that will accept multiple connections and can handle multiple quizes/users at once.

Additionally, quiztakers will enter a unique username. The engine will not allow the same username to take the same quiz over again unless the 'teacher' goes in and deletes the user's .quizresults file.

At the end of the quiz, the user will see their total score as a straight number as well as a percentage. If the quiz contained a flag and the user met the minimum threshold, the flag will also be displayed.

[The source code for the quiz engine can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/takequiz.c)


## Quiz Grader
The quiz grader will generate individual grade files as well as an overall file for the selected quiz. It will create a subdirectory inside the grades/ folder per quiz. 

The individual grade file will display whether the 'student' got the question right or wrong. If wrong, the file will display what answer was expected as well as the user's inputted answer.

The overall grade file will display all user IDs with their scores displayed as straight numbers as well as percentages. At the end of the file, a table will be outputted with statistics per question. This table includes how many 'students' got the question right, wrong, and the percentage correct for each question. The file will also include the total quiz average across all 'students'.

[The source code for the quiz grader can be found here.](https://github.com/cyclawps52/Flag-Quiz-Engine/blob/master/Source/grader.c)

