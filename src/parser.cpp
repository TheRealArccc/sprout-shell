#include "../include/parser.hpp"

ParsedInput parse_input(const std::string& input) {
    ParsedInput result;

    size_t pipe_pos = input.find('|');

    if (pipe_pos != std::string::npos) {
        result.has_pipe = true;

        std::string left_part = input.substr(0, pipe_pos);
        std::string right_part = input.substr(pipe_pos + 1);

        std::stringstream left_stream(left_part);
        std::stringstream right_stream(right_part);

        std::string token;

        while (left_stream >> token) {
            result.left.args.push_back(token);
        }

        while (right_stream >> token) {
            result.right.args.push_back(token);
        }
    } else {
        std::stringstream stream(input);
        
        std::string token;

        while (stream >> token) {
            result.left.args.push_back(token);
        }
    }

    return result;
}