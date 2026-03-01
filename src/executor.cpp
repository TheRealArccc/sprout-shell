#include "../include/executor.hpp"

#include "../include/builtins.hpp"

void execute_command(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        return;
    } else if (is_builtin(tokens[0])) {
        handle_builtin(tokens);
    } else {
        execute_external(tokens);
    }
}

void execute_external(const std::vector<std::string>& tokens) {
    // pid_t pid = fork();

    // if (pid == 0) { // child process
    //     std::vector<char*> args;

    //     for (auto& s : tokens) {
    //         args.push_back(const_cast<char>* (s.c_str()))
    //     }
    // } else if (pid > 0) { // parent process (shell)

    // } else { // fork failed :(
        
    // }
}