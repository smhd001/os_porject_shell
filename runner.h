#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class runner
{
private:
    /* data */
public:
    runner(/* args */);
    ~runner();
    void run(string input);
    void get_first_word_of_line(char *file);
    void get_most_repeated_word(char *file);
    void bash(char *args[]);
};
