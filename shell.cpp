#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <bits/stdc++.h>
#include <setjmp.h>
#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <unistd.h>
#include "shell.h"
#include "runner.h"

using namespace std;
sigjmp_buf ctrlc_buf;

shell::shell(/* args */)
{
    // TODO read history
    shell::user = getenv("USER");
    cout << "Welcome " << shell::user << std::endl;
    read_history (history_file);
}

shell::~shell()
{
    cout << shell::history_file ;
    write_history(history_file);
    cout << "Shell destroyed" << std::endl;
}
void handle_signals(int signo)
{
    if (signo == SIGINT)
    {
        siglongjmp(ctrlc_buf, 1);
    }
}
int shell::start()
{
    cout << "Shell started" << std::endl;
    runner r = runner();
    if (signal(SIGINT, handle_signals) == SIG_ERR)
    {
        cerr << ("failed to register interrupts with kernel\n");
    }
    while (true)
    {
        while (sigsetjmp(ctrlc_buf, 1) != 0)
            ;

        string path = filesystem::current_path();
        string prompt = path + "\n" + "$" + shell::user + ">";
        string input = readline(prompt.c_str());
        if (input == "exit")
        {
            break;
        }
        else if (input != "")
        {
            r.run(input);
            add_history(input.c_str());
        }
    }
    return 0;
}
