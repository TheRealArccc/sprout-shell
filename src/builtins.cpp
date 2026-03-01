#include "../include/builtins.hpp"

std::vector<std::string> commands = {"cd", "echo", "ls", "pwd"};

void ls(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "failed to fork" << std::endl;
        return;
    } else if (pid == 0) {
        std::vector<char*> argv;
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
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

void pwd(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "failed to fork" << std::endl;
    } else if (pid == 0) {
        std::vector<char*> argv;

        for (const auto& arg: args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
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

void cd(const std::vector<std::string>& args) {
    if (chdir(args[0].c_str()) == 0) {
        std::cerr << args[0] << " failed: " << std::strerror(errno) << std::endl;
    }
}

void echo(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "failed to fork" << std::endl;
    } else if (pid == 0) {
        std::vector<char*> argv;

        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
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
    } else if (args[0] == "echo") {
        return echo(args);
    } else if (args[0] == "ls") {
        return ls(args);
    } else if (args[0] == "pwd") {
        return pwd(args);
    }
}