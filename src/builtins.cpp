#include "../include/builtins.hpp"
#include "../include/history.hpp"

std::vector<std::string> commands = {"exit", "cd", "history", "sproutsh", "sprout"};

void sprout(const std::vector<std::string>& args) {
    if (args[1] == "--version") {
        std::cout << "sproutsh " << "0.1.0" << "\n";
        std::cout << "Copyright (c) 2026 TheRealArccc\n\n";

        std::cout << "This is free software; you are free to change and redistribute it.\n";
        std::cout << "There is NO WARRANTY, to the extent permitted by law.\n";
        return;
    } else if (args.size() != 1 && args[1].substr(0, 2) == "--" && args[1].size() > 2) {
        std::cout << args[0] << ": " << args[1] << ": invalid option\n";
        std::cout << "Usage: \n";
        std::cout << "\tsprout [option]\n";
        std::cout << "\tsproutsh [option]\n";
        std::cout << "Options: \n";
        std::cout << "\t--version\n";
        return;
    }
}

void history() {
    print_history();
}

void exit(const std::vector<std::string>& args) {
    std::exit(EXIT_SUCCESS);
}

void cd(const std::vector<std::string>& args) {
    if (chdir(args[1].c_str()) == 0) {

    } else {
        std::cerr << args[0] << " failed: " << std::strerror(errno) << std::endl;
    }

    return;
}

////////////////////

bool is_builtin(const std::string& args) {
    if (std::find(commands.begin(), commands.end(), args) != commands.end()) { // returns commands.end() if not found
        return true;
    } else {
        return false;
    }
}

void handle_builtin(const std::vector<std::string>& args) {
    if (args[0] == "cd") {
        return cd(args);
    } else if (args[0] == "exit") {
        return exit(args);
    } else if (args[0] == "history") {
        return history();
    } else if (args[0] == "sprout" || args[0] == "sproutsh") {
        return sprout(args);
    }
}