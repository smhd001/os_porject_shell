#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class runner
{
private:
public:
    runner();
    ~runner();
    void help();
    void run(string input);
    void get_first_word_of_line(char *file);
    void get_most_repeated_word(char *file);
    void delete_empety_spaces(char *file);
    void get_uncommented_lines(char *file);
    void get_line_number(char *file);
    void get_first_ten_lines(char *file);
    void bash(char *args[]);
    void bash_s(char *command);
};
