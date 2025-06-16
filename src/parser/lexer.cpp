#include "parser/cli_lexer.hpp"
#include "parser/token.hpp"

#include <algorithm>


static bool is_number(std::string input) {
    return (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit));
}

token::Command lexer::tokenize(int argc, char* argv[]) {
    token::Command cmd;
    argc >= 2 ? cmd.type = lexer::tokenize_type(argv[1]) : cmd.type = token::ActionType::NONE;
    argc >= 3 ? cmd.subtype = lexer::tokenize_subtype(argv[2]) : cmd.subtype = token::SubType::NONE;

    int i = 3;
    while (i < argc) {
        token::Arg arg = lexer::tokenize_argument(argv[i]);
        cmd.arguments.push_back(arg);
        ++i;
    }
    return cmd;
}

token::ActionType lexer::tokenize_type (const std::string& input) {
    auto it = token::action_map.find(input);
    return (it == token::action_map.end() ? token::ActionType::UNKNOWN : it->second);
}

token::SubType lexer::tokenize_subtype (const std::string& input) {
    auto it = token::subaction_map.find(input);
    return (it == token::subaction_map.end() ? token::SubType::UNKNOWN : it->second);
}

token::Arg lexer::tokenize_argument (const std::string& input) {
    token::Arg arg;
    if (is_number(input)) {
        arg.type = token::ArgType::INT;
        arg.value = std::stoi(input);
    }
    else {
        arg.type = token::ArgType::STRING;
        arg.value = input;
    }
    return arg;
}