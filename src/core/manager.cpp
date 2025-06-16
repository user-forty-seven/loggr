#include "core/manager.hpp"
#include "errors/errors.hpp"
#include "core/models.hpp"
#include "misc/color.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


manager::TodoManager::TodoManager (const std::string& filename) : file(filename) {}

void manager::TodoManager::add_tool (const std::string& task) {
    json j = load();
    int id = j.size() + 1;

    // models::Time time = utils::get_current_time();

    if (!is_dulicate(task, j)) {
       j.push_back({
        {"id", id}, 
        {"task", task}, 
        {"done", false}
        // {"timestamp", {
        //     {"hour", time.hour},
        //     {"min", time.minute},
        //     {"second", time.second},
        //     {"day", time.day},
        //     {"month", time.month},
        //     {"month_name", time.month_name},
        //     {"year", time.year}
        // }}
       }); 
        save(j);
        std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << "Added task successfully with an id of " << id << "." << std::endl;
    }
    else {
        throw errors::TaskError("\"" + task + "\" already exists.");
    }
    
}

void manager::TodoManager::edit_tool (const int& n, const std::string& task) {
    json j = load();
    if (n > (int)j.size() || n <= 0) {
        throw errors::CommandError("Invalid task id.");
    }
    auto it = j.begin() + n - 1; // since the ids start from one 
    std::string previous_task = (*it)["task"];
    (*it)["task"] = task;
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << "\"" << previous_task << "\" has been edited to " << (*it)["task"] << std::endl;
    save(j);
}

void manager::TodoManager::list_tool (const models::FilterType& filter) {
    json j = load();
    if (j.size() == 0) {
      throw errors::DataError("No tasks added. Try adding one with `loggr add`.");
    }
    for (const auto& item : j) {
        switch (filter) {
            case models::FilterType::MARKED: if(!item["done"]) continue; break;
            case models::FilterType::UNMARKED: if(item["done"]) continue; break;
        }
        std::cout << (item["done"] ? std::string(color::GREEN) + "[X] " : std::string(color::RED) + "[ ] ")  << color::RESET
        << item["id"] << ": "
        << item["task"].get<std::string>() << '\n';
    }
        // else if (filter == models::FilterType::MARKED) {
        //     if (item["done"]) {
        //     std::cout << color::GREEN << "[X] " << color::RESET
        //     << item["id"] << ": "
        //     << item["task"].get<std::string>() << '\n';
        //     }
        // }
        // else if (filter == models::FilterType::UNMARKED) {
        //     std::cout << color::RED <<  "[ ] "  << color::RESET
        //     << item["id"] << ": "
        //     << item["task"].get<std::string>() << '\n';
        // }
}


void manager::TodoManager::delete_tool (const int& n) {
    json j = load();
    if (n > (int)j.size() || n <= 0)  {
        throw errors::CommandError("Invalid task id.");
    }
    auto it = j.begin() + n - 1;
    std::string previous_task = (*it)["task"];
    j.erase(it);
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << "\"" << previous_task << "\" has been deleted successfully." << std::endl;
    save(j, true);
}

void manager::TodoManager::clear_tool (const models::FilterType& filter) {
    switch (filter) {
    case models::FilterType::ALL: truncate(); break;
    case models::FilterType::MARKED: clear_marked(); break;
    }
}

void manager::TodoManager::mark_tool (const int& n) {
    json j = load();
    if (n > (int)j.size() || n <= 0) {
        throw errors::CommandError("Invalid task id.");
    }
    auto it = j.begin() + n - 1;
    (*it)["done"] = true;
    save(j);
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << (*it)["task"] << " has been marked successfully" << std::endl;
}

void manager::TodoManager::unmark_tool (const int& n) {
    json j = load();
    if (n > (int)j.size() || n <= 0) {
        throw errors::CommandError("Invalid task id.");
    }
    auto it = j.begin() + n - 1;
    (*it)["done"] = false;
    save(j);
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << (*it)["task"] << " has been unmarked successfully" << std::endl;
}

void manager::TodoManager::save (json& j, bool fix_ids) {
   std::ofstream f(file);
   if (!f.is_open()) {
    throw errors::DataError("Could not open the data file.");
   }
   if (fix_ids) {
    for (int i = 0; i < (int)j.size(); i++) {
        auto it = j.begin() + i;
        (*it)["id"] = i + 1;
    }
   }
   f << j.dump(4);

   if (f.fail()) {
    throw errors::DataError("Could not save the data.");
   }
}

json manager::TodoManager::load () {
    std::ifstream f(file);
    if (!f) {
       return json::array(); 
    }
    json j; 
    f >> j;
    return j;
}

bool manager::TodoManager::is_dulicate (const std::string& s, const json& j) {
    for (const auto& item : j) {
        if (item["task"] == s) {
            return true;
        }
    }
    return false;
}

void manager::TodoManager::truncate () {
    json j_empty = json::array();
    save(j_empty);
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << "ALL the tasks have been deleted successfully." << std::endl;
}

void manager::TodoManager::clear_marked () {
    json j = load();
    for (auto it = j.begin(); it != j.end(); ) {
        (*it)["done"] ? it = j.erase(it) : ++it;  // if we erase it and then try to increment it, it is undefined behaviuour, so we get the next iterator and set it as the currect iterator (erase returns the next valid iterator)

    }
    save(j, true);
    std::cout << color::GREEN << "[SUCCESS]: " << color::RESET << "All the completed tasks have been deleted successfully." << std::endl;
}
