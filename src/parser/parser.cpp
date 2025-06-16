#include "parser/cli_parser.hpp"
#include "parser/cli_lexer.hpp"
#include "parser/token.hpp"
#include "core/models.hpp"
#include "errors/errors.hpp"
#include "utils/utils.hpp"

using AT = token::ActionType;
using ST = token::SubType;
using ArgT = token::ArgType;
using FT = models::FilterType;

static void parse_add(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_edit(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_remove(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_clear(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_list(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_remove(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_mark(const token::Command& cmd, models::ParsedCommand& parsed_cmd);
static void parse_unmark(const token::Command& cmd, models::ParsedCommand& parsed_cmd);


models::ParsedCommand parser::parse (const token::Command& cmd) {

    AT type = cmd.type;
    ST subtype = cmd.subtype;
    std::vector<token::Arg> arg = cmd.arguments;

    models::ParsedCommand parsed_cmd;

    // begin parsing
    if (type == AT::NONE) {
        throw errors::ParseError(
            "No command provided.",
            "loggr <command> [subcommand] [args...]",
            "Maybe try `loggr help`?"     
        );
    }

    else if (type == AT::UNKNOWN) {
        throw errors::ParseError(
            "Unknown command.",
            "loggr <command> [subcommand] [args...]",
            "Maybe try `loggr help`?"     
        );
    }

    else if (type == AT::HELP && subtype == ST::NONE) {
        parsed_cmd.type = AT::HELP;
        parsed_cmd.subtype = ST::NONE;
    }

    else if (type == AT::INFO && subtype == ST::NONE) {
        parsed_cmd.type = AT::INFO;
        parsed_cmd.subtype = ST::NONE;
    }

    else if (type == AT::ADD && subtype == ST::TASK) {
        parse_add(cmd, parsed_cmd);
    }

    else if (type == AT::EDIT && subtype == ST::TASK) {
        parse_edit(cmd, parsed_cmd);
    }

    else if (type == AT::REMOVE && subtype == ST::TASK) {
        parse_remove(cmd, parsed_cmd);
    }

    else if (type == AT::CLEAR && subtype == ST::TASKS) {
        parse_clear(cmd, parsed_cmd);
    }

    else if (type == AT::LIST && subtype == ST::TASKS) {
        parse_list(cmd, parsed_cmd);
    }

    else if (type == AT::MARK && subtype == ST::TASK) {
        parse_mark(cmd, parsed_cmd);
    }

    else if (type == AT::UNMARK && subtype == ST::TASK) {
        parse_unmark(cmd, parsed_cmd);
    }
    
    else {
        throw errors::ParseError(
            "Invalid command.",
            "",
            "Maybe try `loggr help`?"
        );
    }

    return parsed_cmd;
}

static void parse_add(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
    if (cmd.arguments.size() < 1) {
        throw errors::ParseError(
            "Task description not provided.",
            "loggr add task \"<description>\""
        );
    }
    else if (cmd.arguments.size() > 1) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr add task \"<description>\""
        );
    }
    else if (cmd.arguments[0].type != ArgT::STRING) {
        throw errors::ParseError(
            "Invalid task description",
            "loggr add task \"<description>\""
        );
    }
    else {
        parsed_cmd.type = AT::ADD;
        parsed_cmd.subtype = ST::TASK;
        parsed_cmd.task_description = std::get<std::string>(cmd.arguments[0].value);
        utils::normalize_whitespaces(parsed_cmd.task_description);
    }
}

static void parse_edit(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
    if (cmd.arguments.size() < 2) {
        throw errors::ParseError(
            "Too few arguments provided.",
            "loggr edit <task id> \"<new desc>\""
        );
    }
    else if (cmd.arguments.size() > 2) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr edit <task id> \"<new desc>\""
        );
    }
    else if (cmd.arguments[0].type != ArgT::INT || cmd.arguments[1].type != ArgT::STRING) {
        throw errors::ParseError(
            "Incorrect use of command.",
            "loggr edit <task id> \"<new desc>\""
        );
    }
    else {
        parsed_cmd.type = AT::EDIT;
        parsed_cmd.subtype = ST::TASK;
        parsed_cmd.task_id = std::get<int>(cmd.arguments[0].value);
        parsed_cmd.task_description = std::get<std::string>(cmd.arguments[1].value);
        utils::normalize_whitespaces(parsed_cmd.task_description);
    }
}

static void parse_remove(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
   if (cmd.arguments.size() < 1) {
        throw errors::ParseError(
            "Task id not provided.",
            "loggr remove task <task id>"
        );
    }
    else if (cmd.arguments.size() > 1) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr remove task <task id>"
        );
    }
    else if (cmd.arguments[0].type != ArgT::INT) {
        throw errors::ParseError(
            "Invalid task id provided.",
            "loggr remove task <task id>"
        );
    }
    else {
        parsed_cmd.type = AT::REMOVE;
        parsed_cmd.subtype = ST::TASK;
        parsed_cmd.task_id = std::get<int>(cmd.arguments[0].value);
    }   
}

static void parse_clear(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
    if (cmd.arguments.size() < 1) {
        throw errors::ParseError(
            "Type of task not provided.",
            "loggr clear tasks all/completed"
        );
    }
    else if (cmd.arguments.size() > 1) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr clear tasks all/completed"
        );
    }
    else if (cmd.arguments[0].type != ArgT::STRING) {
        throw errors::ParseError(
            "Invalid task type.",
            "loggr clear tasks all/completed"
        );
    }
    else {
        std::string task_type = std::get<std::string>(cmd.arguments[0].value);
        parsed_cmd.type = AT::CLEAR;
        parsed_cmd.subtype = ST::TASKS;
        if (task_type == "all") {
           parsed_cmd.filter = FT::ALL;
        }
        else if (task_type == "completed") {
            parsed_cmd.filter = FT::MARKED;
        }
        else {
            throw errors::ParseError(
                "Invalid filter type.",
                "loggr clear tasks all/completed"
            );
        }
    }
}

static void parse_list(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
    if (cmd.arguments.size() == 0) {
        parsed_cmd.type = AT::LIST;
        parsed_cmd.subtype = ST::TASKS;
        parsed_cmd.filter = FT::ALL;
    } 
    else if (cmd.arguments.size() > 1){
        throw errors::ParseError(
            "Too many arguments.",
            "loggr list tasks marked/unmarked"
        );
    }
    else if (std::get<std::string>(cmd.arguments[0].value) == "marked"){
        parsed_cmd.type = AT::LIST;
        parsed_cmd.subtype = ST::TASKS;
        parsed_cmd.filter = FT::MARKED;
    }
    else if (std::get<std::string>(cmd.arguments[0].value) == "unmarked"){
        parsed_cmd.type = AT::LIST;
        parsed_cmd.subtype = ST::TASKS;
        parsed_cmd.filter = FT::UNMARKED;
    }
    else {
        throw errors::ParseError(
            "Invalid filter type.",
            "loggr list tasks marked/unmarked"
        );
    }
}

static void parse_mark(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
   if (cmd.arguments.size() < 1) { throw errors::ParseError(
            "Task id not provided.",
            "loggr mark task <task id>"
        );
    }
    else if (cmd.arguments.size() > 1) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr mark task <task id>"
        );
    }
    else if (cmd.arguments[0].type != ArgT::INT) {
        throw errors::ParseError(
            "Invalid task id provided.",
            "loggr mark task <task id>"
        );
    }
    else {
        parsed_cmd.type = AT::MARK;
        parsed_cmd.subtype = ST::TASK;
        parsed_cmd.task_id = std::get<int>(cmd.arguments[0].value);
    }   
}

static void parse_unmark(const token::Command& cmd, models::ParsedCommand& parsed_cmd) {
   if (cmd.arguments.size() < 1) {
        throw errors::ParseError(
            "Task id not provided.",
            "loggr unmark task <task id>"
        );
    }
    else if (cmd.arguments.size() > 1) {
        throw errors::ParseError(
            "Too many arguments provided.",
            "loggr unmark task <task id>"
        );
    }
    else if (cmd.arguments[0].type != ArgT::INT) {
        throw errors::ParseError(
            "Invalid task id provided.",
            "loggr unmark task <task id>"
        );
    }
    else {
        parsed_cmd.type = AT::UNMARK;
        parsed_cmd.subtype = ST::TASK;
        parsed_cmd.task_id = std::get<int>(cmd.arguments[0].value);
    }   
}
