#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <array>

#include <fcntl.h>

#include "parser.hpp"

void execute_command(const ParsedInput& input);
void execute_external(const std::vector<std::string>& tokens);

#endif