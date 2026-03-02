#include "../include/builtins.hpp"

std::vector<std::string> commands = {"exit", "cd", "echo", "ls", "pwd", "mkdir"};

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

void mkdir(const std::vector<std::string>& args) {
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
    } else if (args[0] == "exit") {
        return exit(args);
    } else if (args[0] == "mkdir") {
        return mkdir(args);
    }
}