#include "runner.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;
#define ASCII_RED "\033[0;31m"
#define ASCII_NORMAL "\033[0m"
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
void runner::help()
{
    cout << "Commands:" << endl;
    cout << "fwl file - get first words of lines" << endl;
    cout << "mrw file - get most repeated word" << endl;
    cout << "des file - delete empety spaces" << endl;
    cout << "ul file - get uncommented lines" << endl;
    cout << "ln file - get line number" << endl;
    cout << "ftl file - get first ten lines" << endl;
    cout << "cd dir - change directory" << endl;
    cout << "exit - exit shell" << endl;
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
    else if (strcmp(args[0], "mrw") == 0)
    {
        get_most_repeated_word(args[1]);
    }
    else if (strcmp(args[0], "des") == 0)
    {
        delete_empety_spaces(args[1]);
    }
    else if (strcmp(args[0], "ul") == 0)
    {
        get_uncommented_lines(args[1]);
    }
    else if (strcmp(args[0], "ln") == 0)
    {
        get_line_number(args[1]);
    }
    else if (strcmp(args[0], "ftl") == 0)
    {
        get_first_ten_lines(args[1]);
    }
    else if (strcmp(args[0], "help") == 0)
    {
        help();
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        chdir(args[1]);
    }
    else
    {
        bash(args);
    }
}
void runner::bash(char *args[])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // child
        if (execvp(args[0], args) < 0)
        {
            cerr << ASCII_RED << "Error executing command" << ASCII_NORMAL << endl;
        };
        exit(0);
    }
    else
    {
        // parent
        wait(NULL);
    }
}
void runner::bash_s(char *command)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (system(command) < 0)
        {
            cerr << ASCII_RED << "Error executing command" << ASCII_NORMAL << endl;
        };
        cout << endl;
        exit(0);
    }
    else
    {
        // parent
        wait(NULL);
    }
}
void runner::get_first_word_of_line(char *file)
{
    char *args[] = {"cut", file, "-d", " ", "-f", "1", NULL};
    bash(args);
}
void runner::get_most_repeated_word(char *file)
{
    char command[1000];
    sprintf(command, "tr -s ' ' '\n' < %s | sort | uniq -c | sort -nr | head -n 1 | cut -d ' ' -f 8", file);
    bash_s(command);
}
void runner::delete_empety_spaces(char *file)
{
    char command[1000];
    sprintf(command, "tr -d ' \t\n\r' < %s ", file);
    bash_s(command);
}
void runner::get_uncommented_lines(char *file)
{
    // grep -v '^#' file is a optoin too
    char *args[] = {"grep", "-o", "'^[^#]*'", file, NULL};
    bash(args);
}
void runner::get_line_number(char *file)
{
    char *args[] = {"wc", "-l", file, NULL};
    bash(args);
}
void runner::get_first_ten_lines(char *file)
{
    char *args[] = {"head", "-n", "10", file, NULL};
    bash(args);
}