#include <iostream>

#include "../include/shell.hpp"
#include "../include/parser.hpp"
#include "../include/executor.hpp"

namespace fs = std::filesystem;

void shell() {
    while (true) {
        fs::path cwd;

        try {
            cwd = fs::current_path().c_str();
        } catch (const fs::filesystem_error& e) {
            std::cerr << "error: " << e.what() << std::endl;
        }

        std::cout << "~" << cwd.string() << " $ ";
        
        std::string input;
        std::getline(std::cin, input);  // Read full line including spaces

        // Tokenise
        const auto tokens = parse_input(input);
        
        // Debug output for tokens
        std::cout << "\nParsed command:\n";
        std::cout << "Has pipe: " << (tokens.has_pipe ? "true" : "false") << "\n";
        std::cout << "Left args: ";
        for (const auto& arg : tokens.left.args) {
            std::cout << "[" << arg << "] ";
        }
        std::cout << "\n";
        
        if (tokens.has_pipe) {
            std::cout << "Right args: ";
            for (const auto& arg : tokens.right.args) {
                std::cout << "[" << arg << "] ";
            }
            std::cout << "\n";
        }
        
        execute_command(tokens);
    }
}