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
    cout << "Shell created" << std::endl;
    // TODO read history
}
shell::~shell()
{
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
        printf("failed to register interrupts with kernel\n");
    }
    while (true)
    {
        while (sigsetjmp(ctrlc_buf, 1) != 0)
            ;

        string path = filesystem::current_path();
        string prompt = path + "\n" + "$>";
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
