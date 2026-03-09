#include "../include/parser.hpp"
#include <sstream>

ParsedInput parse_input(const std::string& input) {
    ParsedInput result;

    std::stringstream pipe_stream(input);
    std::string segment;

    while (std::getline(pipe_stream, segment, '|')) {
        Command cmd;

        std::stringstream token_stream(segment);
        std::string token;

        while (token_stream >> token) {
            cmd.args.push_back(token);
        }

        result.pipeline.push_back(cmd);
    }

    return result;
}