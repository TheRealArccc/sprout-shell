#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

bool is_builtin(const std::string& args);
void handle_builtin(const std::vector<std::string>& args);

void cd(const std::vector<std::string>& args);
void exit(const std::vector<std::string>& args);

#endif