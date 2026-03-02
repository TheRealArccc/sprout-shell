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

void execute_external(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "failed to fork" << std::endl;
    } else if (pid == 0) {
        std::vector<char*> argv;

        for (const auto& arg : args) {
            argv.push_back(const_cast<char*> (arg.c_str()));
        }

        argv.push_back(nullptr);
        
        if (execvp(argv[0], argv.data()) == -1) {
            std::cerr << argv[0] << " failed: " << std::strerror(errno) << std::endl;
            _exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}