#include <iostream>
#include <string>

#include <signal.h>

#include "../include/shell.hpp"

// signal interrupt
void sigint_handler(int sig) {
    return;
}

int main() {
    // signal interrupt
    signal(SIGINT, sigint_handler);

    shell();

    return 0;
}