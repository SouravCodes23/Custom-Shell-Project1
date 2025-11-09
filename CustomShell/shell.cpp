#include "shell.h"
#include <iostream>

void Shell::init() {
    prompt = "CustomShell> ";
    std::cout << "Welcome to Custom Shell!" << std::endl;
}

void Shell::set_prompt(const std::string& new_prompt) {
    prompt = new_prompt;
}

std::string Shell::get_prompt() const {
    return prompt;
}
