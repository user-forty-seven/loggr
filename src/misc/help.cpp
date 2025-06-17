#include "misc/help.hpp"
#include "misc/color.hpp"

#include <iostream>
#include <iomanip>

#define WIDTH 45


using namespace color;

void help::full_help() {

    std::cout << BOLD_GREEN << "loggr - Personal CLI Organizer for Tasks" << RESET << '\n'
    << BOLD << "USAGE: " << BLUE << "loggr <command> [subcommand] [args...]" << RESET << "\n\n"

    << BOLD << "Task Management:\n" << RESET
    << std::left << std::setw(WIDTH) << "  loggr add task \"<description>\"" << CYAN << "Add a new task" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr edit task <task id> \"<new desc>\"" << CYAN << "Edit an existing task" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr remove task <task id>" << CYAN << "Delete a specific task" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr clear tasks all" << YELLOW << "Delete ALL tasks (confirmation required)" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr clear tasks completed" << CYAN << "Delete all marked (done) tasks" << RESET << "\n\n"

    << BOLD << "Listing:\n"  << RESET 
    << std::left << std::setw(WIDTH) << "  loggr list tasks" << CYAN << "List all tasks" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr list tasks marked" << CYAN << "List only completed/marked tasks" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr list tasks unmarked" << CYAN << "List only pending/unmarked tasks" << RESET << "\n\n"

    << BOLD << "Status Actions:\n" << RESET 
    << std::left << std::setw(WIDTH) << "  loggr mark task <task id>" << CYAN << "Mark a task as done" << RESET << '\n' 
    << std::left << std::setw(WIDTH) << "  loggr unmark task <task id>" << CYAN << "Unmark a completed task" << RESET << "\n\n"

    << BOLD << "Utilities:\n" << RESET 
    << std::left << std::setw(WIDTH) << "  loggr help" << CYAN << "Display this help message" << RESET << '\n'
    << std::left << std::setw(WIDTH) << "  loggr info" << CYAN << "Display some general info" << RESET << "\n\n"

    << BOLD << "Examples:\n" << RESET 
    << std::left << std::setw(WIDTH) << "  loggr add task \"Finish maths homework\"" << '\n'
    << std::left << std::setw(WIDTH) << "  loggr list tasks" << '\n'
    << std::left << std::setw(WIDTH) << "  loggr mark task 1" << '\n'
    << std::left << std::setw(WIDTH) << "  loggr clear tasks completed" << '\n'
    << std::left << std::setw(WIDTH) << "  loggr remove task 4" << "\n\n";
    
}
