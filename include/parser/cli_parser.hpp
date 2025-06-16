#pragma once
#include "parser/cli_parser.hpp"
#include "core/models.hpp"
#include "parser/token.hpp"

namespace parser {
   models::ParsedCommand parse(const token::Command &cmd);
   // void parse_add(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_edit(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_remove(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_clear(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_list(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_remove(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_mark(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
   // void parse_unmark(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
}