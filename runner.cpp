#include "runner.h"
#include<iostream>
#include <unistd.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
using namespace std;


// r = p
runner::runner(/* args */)
{
}
runner::~runner()
{
}
void parse(char *input, char *args[])
{
    int i = 0;
    while (input != NULL)
    {
        args[i] = strsep(&input, " ");
        i++;
    }
    args[i] = NULL;
}
void runner::run(string input)
{
    char *args[100];
    parse((char *)input.c_str(), args);
    // cout << "Running: " << args[0] << endl;
    // cout << "Args: " << endl;
    // for (int i = 0; args[i] != NULL; i++)
    // {
    //     cout << args[i] << endl;
    // }
    if (strcmp(args[0], "fwl") == 0)
    {
        get_first_word_of_line(args[1]);
    }
    if (strcmp(args[0], "mrw") == 0)
    {
        get_most_repeated_word(args[1]);
    }
    if (strcmp(args[0], "cd") == 0)
    {
        chdir(args[1]);
    }
    
    bash(args);
}
void runner::bash(char * args[])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        //child
        execvp(args[0], args);
        exit(0);
    }
    else
    {
        //parent
        wait(NULL);
    }
}
void runner::get_first_word_of_line(char *file)
{
    cout << "Getting first word of line" << endl;
    char *args[] = {"cut", file,"-d", " ", "-f", "1", NULL};
    bash(args);
}
void runner::get_most_repeated_word(char *file)
{
    //tr -s ' ' '\n' < file | sort | uniq -c | sort -nr | head -n 1
    //NOT SUR IF IT WORKS
    char command[1000];
    pid_t pid = fork();
    if (pid == 0)
    {
        sprintf(command, "tr -s ' ' '\n' < %s | sort | uniq -c | sort -nr | head -n 1 | cut -d ' ' -f 8", file);
        system(command);
        exit(0);
    }
    else
    {
        //parent
        wait(NULL);
    }
}