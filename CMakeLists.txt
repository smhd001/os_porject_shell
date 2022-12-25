cmake_minimum_required(VERSION 3.0.0)
project(shell VERSION 0.1.0)


add_executable(shell_os main.cpp shell.cpp runner.cpp)
target_link_libraries(shell_os readline)