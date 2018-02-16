#include <stdio.h>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #include <unistd.h>
#endif
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
#endif

#include "custom.h"

//UTILITY

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

void clear()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}