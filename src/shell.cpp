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
        std::getline(std::cin, input);

        // Tokenise
        const std::vector<std::string>& tokens = tokenise(input);

        execute_command(tokens);
    }
}