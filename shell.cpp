#include<iostream>
#include<readline/readline.h>
#include<readline/history.h>
#include<bits/stdc++.h>
#include "shell.h"

shell::shell(/* args */)
{
    std::cout << "Shell created" << std::endl;
    //TODO read history
}
shell::~shell()
{
    std::cout << "Shell destroyed" << std::endl;
}
int shell::start()
{
    std::cout << "Shell started" << std::endl;
    while (true)
    {
        std::string s = std::filesystem::current_path();
        std::string prompt = s + "\n" + "$> ";
        std::string str = readline(prompt.c_str());
        if (str == "exit")
        {
            break;
        }
        else
        {
            add_history(str.c_str());
        }
    }
}
