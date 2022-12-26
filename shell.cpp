#include<iostream>
#include<readline/readline.h>
#include<readline/history.h>
#include<bits/stdc++.h>
#include "shell.h"
#include "runner.h"

using namespace std;

shell::shell(/* args */)
{
    cout << "Shell created" << std::endl;
    //TODO read history
}
shell::~shell()
{
    cout << "Shell destroyed" << std::endl;
}
int shell::start()
{
    cout << "Shell started" << std::endl;
    runner r = runner();
    while (true)
    {
        string path = filesystem::current_path();
        string prompt = path + "\n" + "$>";
        string input = readline(prompt.c_str());
        if (input == "exit")
        {
            break;
        }
        else if(input != "" )
        {
            r.run(input);
            add_history(input.c_str());
        }
    }
    return 0;
}
