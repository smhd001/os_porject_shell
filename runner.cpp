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
runner::runner()
{
}
runner::~runner()
{
}
void parse(char *input, char *args[])
{
    int i = 0;
	while(true)
    {
		args[i] = strsep(&input, " ");
		if (args[i] == NULL)
			break;
		if (strlen(args[i]) == 0)
			i--;
        i++;
	}
    //args[i] = NULL;
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
    if (input.find("|") != string::npos)
    {
        string command = input.substr(0, input.find("|"));
        string command2 = input.substr(input.find("|") + 1, input.length());
        parse((char *)command.c_str(), args);
        char *args2[100];
        parse((char *)command2.c_str(), args2);
        exe_with_pip(args, args2);
    }
    else
    {
        parse((char *)input.c_str(), args);

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
            exe(args);
        }
    }
}
void runner::exe(char *args[])
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
void runner::exe_with_pip(char *args[], char *args2[])
{
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid == 0)
    {
        // child
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); //dup fd 1 to stdin
        close(fd[1]);
        if (execvp(args[0], args) < 0)
        {
            cerr << ASCII_RED << "Error executing command" << ASCII_NORMAL << endl;
        };
        exit(0);
    }
    else
    { 
        wait(NULL);
        // parent
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            // child
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO); //dup fd 0 to stdout
            close(fd[0]);
            if (execvp(args2[0], args2) < 0)
            {
                cerr << ASCII_RED << "Error executing command" << ASCII_NORMAL << endl;
            };
            exit(0);
        }
        else
        {
            // parent
            close(fd[1]);
            close(fd[0]);
            wait(NULL);
        }
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
    exe(args);
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
    exe(args);
}
void runner::get_line_number(char *file)
{
    char *args[] = {"wc", "-l", file, NULL};
    exe(args);
}
void runner::get_first_ten_lines(char *file)
{
    char *args[] = {"head", "-n", "10", file, NULL};
    exe(args);
}