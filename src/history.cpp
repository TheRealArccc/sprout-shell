#include <iostream>

#include "../include/history.hpp"

static std::vector<std::string> history;

void add_history(const std::string& command) {
    if (!command.empty()) {
        history.push_back(command);
    }

    return;
}

void print_history() {
    for (int i = 0; i < history.size(); i++) {
        std::cout << i + 1 << "  " << history[i] << "\n";
    }
}