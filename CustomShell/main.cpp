#include <iostream>
#include <string>
#include <vector>
#include <process.h>
#include <windows.h>
#include <fcntl.h>
#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "job_control.h"

int main() {
    Shell shell;
    shell.init();

    while (true) {
        std::string input;
        std::cout << "CustomShell> ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        std::vector<std::string> tokens = Parser::parse(input);
        if (tokens.empty()) continue;

        if (tokens[0] == "exit") break;

        // Handle built-in commands
        if (tokens[0] == "jobs") {
            JobControl::list_jobs();
            continue;
        } else if (tokens[0] == "fg") {
            if (tokens.size() > 1) {
                JobControl::bring_to_foreground(std::stoi(tokens[1]));
            }
            continue;
        } else if (tokens[0] == "bg") {
            if (tokens.size() > 1) {
                JobControl::bring_to_background(std::stoi(tokens[1]));
            }
            continue;
        }

        // Execute command
        Executor::execute(tokens);
    }

    return 0;
}
