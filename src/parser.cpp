#include "../include/parser.hpp"

std::vector<std::string> tokenise(const std::string& input) {
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    while(ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
