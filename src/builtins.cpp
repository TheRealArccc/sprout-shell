#include "../include/builtins.hpp"

std::vector<std::string> commands = {"exit", "cd"};

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
    }
}