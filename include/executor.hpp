#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <unistd.h>
// Removed Unix-specific header
#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"

void execute_command(const ParsedInput& input);
void execute_external(const std::vector<std::string>& tokens);

#endif