#ifndef SHELL_H
#define SHELL_H

#include <string>

class Shell {
public:
    void init();
    void set_prompt(const std::string& prompt);
    std::string get_prompt() const;
private:
    std::string prompt;
};

#endif
