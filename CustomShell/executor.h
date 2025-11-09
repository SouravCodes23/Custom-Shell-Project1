#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>

class Executor {
public:
    static void execute(const std::vector<std::string>& tokens);
private:
    static void execute_single_command(const std::vector<std::string>& cmd);
    static void handle_redirection(const std::vector<std::string>& cmd);
    static void handle_piping(const std::vector<std::string>& cmd);
};

#endif
