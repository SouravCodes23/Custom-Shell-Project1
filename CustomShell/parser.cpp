#include "parser.h"
#include <string>
#include <vector>

std::vector<std::string> Parser::parse(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == '"') {
            in_quotes = !in_quotes;
            token += c;  // Include quotes in token for cmd.exe
        } else if (c == ' ' && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}
