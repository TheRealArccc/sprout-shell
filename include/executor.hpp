#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <iostream>

void execute_command(const std::vector<std::string>& tokens);
void execute_external(const std::vector<std::string>& tokens);

#endif