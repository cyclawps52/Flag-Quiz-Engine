#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include "delete.h"
#include "../custom/custom.h"

int teacherDelete()
{
	clear();
	
	char toDeletePath[350];

	//display deletion menu
	printf("1. Demote User (turn teacher account into student)\n");
	printf("2. Remove User Completely\n");
	printf("3. Remove Test Dump (Prevent students from looking at quiz)\n");
	printf("4. Remove Results (Removes non-graded quiz attempts)\n");
	printf("5. Remove grades (Ex: graded too early)\n");
	printf("6. Soft Delete Quiz (No one can take the quiz, but grades/dumps persist)\n");
	printf("7. Hard Delete Quiz (Destroys quiz, grades, dumps, everything)\n");
	printf("8. Factory Reset (first time run/OOBE)\n");
	printf("\tWhat do you want to do: ");
	int menuChoice;
	fflush(stdin);
	if(scanf("%d", &menuChoice) == 0)
	{
		printf("Invalid option!\n");
		pete();
		return 1;
	}

	switch(menuChoice)
	{
		

		default:
			printf("Invalid option!\n");
			pete();
			return 1;
	}

    pete();
	return 0;
}

int remove_directory(const char *path)
{
	/*
	I take no credit for this function. This was found at 
	https://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c
	and taken from the marked answer written by asveikau.
	*/

	DIR *d = opendir(path);
	size_t path_len = strlen(path);
	int r = -1;

	if (d)
	{
	  struct dirent *p;

	  r = 0;

	  while (!r && (p=readdir(d)))
	  {
	      int r2 = -1;
	      char *buf;
	      size_t len;

	      /* Skip the names "." and ".." as we don't want to recurse on them. */
	      if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
	      {
	         continue;
	      }

	      len = path_len + strlen(p->d_name) + 2; 
	      buf = malloc(len);

	      if (buf)
	      {
	         struct stat statbuf;

	         snprintf(buf, len, "%s/%s", path, p->d_name);

	         if (!stat(buf, &statbuf))
	         {
	            if (S_ISDIR(statbuf.st_mode))
	            {
	               r2 = remove_directory(buf);
	            }
	            else
	            {
	               r2 = unlink(buf);
	            }
	         }

	         free(buf);
	      }

	      r = r2;
	  }

	  closedir(d);
	}

	if (!r)
	{
	  r = rmdir(path);
	}
}