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
    int n = input.pipeline.size();

    if (n == 0) {
        return;
    } else if (n == 1) {
        if (input.pipeline[0].args.empty()) {
            return;
        } else if (is_builtin(input.pipeline[0].args[0])) {
            handle_builtin(input.pipeline[0].args);
        } else {
            pid_t pid = fork();

            if (pid == 0) {
                signal(SIGINT, SIG_DFL);

                if (!input.pipeline[0].input_file.empty()) {
                    int fd = open(input.pipeline[0].input_file.c_str(), O_RDONLY);

                    if (fd < 0) {
                        perror("open input");
                        _exit(EXIT_FAILURE);
                    }

                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }

                if (!input.pipeline[0].output_file.empty()) {
                    int flags = O_WRONLY | O_CREAT;

                    if (input.pipeline[0].append) {
                        flags |= O_APPEND;
                    } else {
                        flags |= O_TRUNC;
                    }

                    int fd = open(input.pipeline[0].output_file.c_str(), flags, 0644);

                    if (fd < 0) {
                        perror("open output");
                        _exit(EXIT_FAILURE);
                    }

                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }

                auto argv = vec_to_cargs(input.pipeline[0].args);

                execvp(argv[0], argv.data());

                std::cerr << argv[0] << " failed: " << std::strerror(errno) << std::endl;
                _exit(EXIT_FAILURE);
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
            } else {
                std::cerr << "failed to fork" << std::endl;
            }
        }

        return;
    }

    // n > 1 (piped commands)

    std::vector<std::array<int, 2>> pipes(n - 1);

    for (int i = 0; i < n - 1; i++) {
        if (pipe(pipes[i].data()) < 0) {
            perror("pipe failed");
            return;
        }
    }

    std::vector<pid_t> children;

    for (int i = 0; i < n; i++) {
        if (input.pipeline[i].args.empty()) {
            return;
        } else if (is_builtin(input.pipeline[i].args[0])) {
            handle_builtin(input.pipeline[i].args);
        } else {
            pid_t pid = fork();

            // child process
            if (pid == 0) {
                signal(SIGINT, SIG_DFL);

                if (i > 0) {
                    dup2(pipes[i-1][0], STDIN_FILENO);
                }
                
                if (i < n - 1) {
                    dup2(pipes[i][1], STDOUT_FILENO);
                }

                /////////////// REDIRECTION ///////////////
                if (!input.pipeline[i].input_file.empty()) {
                    int fd = open(input.pipeline[i].input_file.c_str(), O_RDONLY);

                    if (fd < 0) {
                        perror("open input");
                        _exit(EXIT_FAILURE);
                    }

                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }

                if (!input.pipeline[i].output_file.empty()) {
                    int flags = O_WRONLY | O_CREAT;

                    if (input.pipeline[i].append) {
                        flags |= O_APPEND;
                    } else {
                        flags |= O_TRUNC;
                    }

                    int fd = open(input.pipeline[i].output_file.c_str(), flags, 0644);

                    if (fd < 0) {
                        perror("open output");
                        _exit(EXIT_FAILURE);
                    }

                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }

                for (auto& p : pipes) {
                    close(p[0]);
                    close(p[1]);
                }

                auto argv = vec_to_cargs(input.pipeline[i].args);

                execvp(argv[0], argv.data());

                std::cerr << argv[0] << " failed: " << std::strerror(errno) << std::endl;
                _exit(EXIT_FAILURE);
            }

            children.push_back(pid);
        }
    }

    for (auto& p : pipes) {
        close(p[0]);
        close(p[1]);
    }

    for (auto& pid : children) {
        waitpid(pid, nullptr, 0);
    }

    return;
}

void execute_external(const std::vector<std::string>& args) {
    // pid_t pid = fork();

    // if (pid < 0) {
    //     std::cerr << "failed to fork" << std::endl;
    // } else if (pid == 0) {
    //     auto argv = vec_to_cargs(args);
        
    //     if (execvp(argv[0], argv.data()) == -1) {
    //         std::cerr << argv[0] << " failed: " << std::strerror(errno) << std::endl;
    //         _exit(EXIT_FAILURE);
    //     }
    // } else {
    //     int status;
    //     waitpid(pid, &status, 0);
    // }
}