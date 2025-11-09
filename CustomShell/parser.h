#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class Parser {
public:
    static std::vector<std::string> parse(const std::string& input);
};

#endif
