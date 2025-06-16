#pragma once
#include "parser/token.hpp"

using AT = token::ActionType;
using ST = token::SubType;

namespace lexer {
    token::Command tokenize(int argc, char* argv[]);
    AT tokenize_type(const std::string &input);
    ST tokenize_subtype(const std::string &input);
    token::Arg tokenize_argument(const std::string &input);
} // namespace lexer
