#include <iostream>
#include "shell.h"
using namespace std;
int main(int argc, char const *argv[])
{
    shell s = shell();
    s.start();
    return 0;
}
