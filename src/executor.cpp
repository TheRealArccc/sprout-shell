#include "../include/executor.hpp"

#include "../include/builtins.hpp"

static std::vector<char*> vec_to_cargs(const std::vector<std::string>& args) {
    std::vector<char*> cargs;

    for (const auto& arg : args) {
        cargs.push_back(const_cast<char*>(arg.c_str()));
    }

    cargs.push_back(nullptr);
    return cargs;
}

void execute_command(const ParsedInput& input) {
    if (!input.has_pipe) {
        auto left_args = input.left.args;
        if (left_args.empty()) {
            return;
        } else if (is_builtin(left_args[0])) {
            handle_builtin(left_args);
        } else {
            execute_external(left_args);
        }

        return;
    }
}

void execute_external(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "failed to fork" << std::endl;
    } else if (pid == 0) {
        auto argv = vec_to_cargs(args);
        
        if (execvp(argv[0], argv.data()) == -1) {
            std::cerr << argv[0] << " failed: " << std::strerror(errno) << std::endl;
            _exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}