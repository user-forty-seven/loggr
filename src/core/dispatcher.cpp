#include "core/dispatcher.hpp"
#include "core/models.hpp"
#include "parser/token.hpp"
#include "core/manager.hpp"
#include "utils/utils.hpp"
#include "misc/help.hpp"
#include "misc/color.hpp"
#include "errors/errors.hpp"
#include "misc/info.hpp"

#include <string>
#include <iostream>


using AT = token::ActionType;
using ST = token::SubType;
using FT = models::FilterType;


static bool confirm();
static bool more_confirm();
static bool prompt_user(const std::string& prompt);

void dispatcher::dispatch (const models::ParsedCommand& cmd) {

    std::string data_path = utils::get_data_path();
    manager::TodoManager manager(data_path);

    switch (cmd.type) {
    case AT::HELP: help::full_help(); break;
    case AT::INFO: info::show_info(); break;
    case AT::ADD: manager.add_tool(cmd.task_description); break;
    case AT::LIST: manager.list_tool(cmd.filter); break;
    case AT::EDIT: manager.edit_tool(cmd.task_id, cmd.task_description); break;
    case AT::REMOVE: if (prompt_user("Are you sure?[yes/no]")) manager.delete_tool(cmd.task_id);  else throw errors::ConfirmationError("Aborted."); break;
    case AT::CLEAR: if (prompt_user("Are you sure?[yes/no]") && prompt_user("Are you" + std::string(color::RED) +  " REALLY " + color::YELLOW + "sure? This action" + color::RED + " CANNOT " + color::YELLOW + "be undone.[yes/no]")) manager.clear_tool(cmd.filter); else throw errors::ConfirmationError("Aborted."); break;

    case AT::MARK: manager.mark_tool(cmd.task_id); break;
    case AT::UNMARK: manager.unmark_tool(cmd.task_id); break;
    }
}

static bool prompt_user(const std::string& prompt) {
    std::string input;
    std::cout << color::YELLOW << prompt << color::RESET << "\n> ";
    std::getline(std::cin, input);
    utils::normalize_whitespaces(input);
    return input == "yes";
}

