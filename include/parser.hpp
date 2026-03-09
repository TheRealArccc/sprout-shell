#ifndef PARSER_HPP
#define PARSER_HPP

#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct Command {
    std::vector<std::string> args;
};

struct ParsedInput {
    std::vector<Command> pipeline;
};

ParsedInput parse_input(const std::string& input);
// std::vector<std::vector<std::string>> tokenise(const std::string& input);

#endif