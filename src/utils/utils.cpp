#include "utils/utils.hpp"
#include "core/models.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> // for getenv
#include <filesystem>
#include <algorithm>
#include <chrono>
#include <array>

std::string utils::get_data_path() {
    const char* home = std::getenv("HOME"); 
    std::filesystem::path data_path;
    if (home) {
        data_path = std::filesystem::path(home) / ".local" / "share" / "loggr" / "data";
        std::filesystem::create_directories(data_path);
        if (!std::filesystem::exists(data_path)) {
            throw std::runtime_error("Unable to set the data directory");
        }
    }
    else {
        throw std::runtime_error("Unable to get the HOME environment variable, are you sure its correct?");
    }
    return (data_path / "data.json").string();
}

void utils::normalize_whitespaces(std::string& s) {
    auto begin_it = std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); }); // find the first non space character from the beginning

    auto end_it = std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isspace(c); }).base(); // find the first non space character from the end

    if (begin_it >= end_it) { // this means that is string is empty
        s.clear();
        return;
    }

    // create trimmed string
    std::string trimmed(begin_it, end_it);

    // now collapse multiple spaces into a single space
    std::string result; 
    bool in_space = false;

    for(char ch: trimmed) {
        if (std::isspace(ch) && !in_space) {
            result.push_back(' ');
            in_space = true; // we are now in a space
        }
        else if (!std::isspace(ch)){
            result.push_back(ch);
            in_space = false; // we are no longer in the space
        }
    }

    s = std::move(result); // assign the result to the orginal string
}

models::Time utils::get_current_time() {
  models::Time time;
  // get current time as a time_point
  auto now = std::chrono::system_clock::now();

  // convert to system time (time_t) to use with ctime
  std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

  // convert to local time (struct tm)
  std::tm now_tm = *std::localtime(&now_time_t);

  // a vector to hold the month names
  const std::array<std::string, 12> month_names = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
  };

  // extract the individual components
  time.year = now_tm.tm_year + 1900; // since tm_year is years since 1900
  time.month = now_tm.tm_mon + 1; // since tm_mon is 0..11
  time.month_name = month_names[now_tm.tm_mon];
  time.day = now_tm.tm_mday;
  time.hour = now_tm.tm_hour;
  time.minute = now_tm.tm_min;
  time.second = now_tm.tm_sec;

  return time;
}

void utils::print_tokens (const token::Command& cmd) {
  std::cout << std::left;
  std::cout << std::setw(10) << "TYPE"     << ": " << token::action_map_reverse.at(cmd.type) << '\n';
  std::cout << std::setw(10) << "SUBTYPE"  << ": " << token::subaction_map_reverse.at(cmd.subtype) << '\n';

  if (cmd.arguments.size() == 0) {
    std::cout << std::setw(10) << "ARGUMENTS" << ": " << "none" << std::endl;
  }
  else {
    std::cout << std::setw(10) << "ARGUMENTS" << ":\n";
    std::cout << "  # | " << std::setw(7) << "TYPE" << " | VALUE\n";
    std::cout << " ---+--------+----------------\n";
    for (size_t i = 0; i < cmd.arguments.size(); ++i) {
        std::cout << ' ' << std::setw(2) << i + 1 << " | ";
        if (cmd.arguments[i].type == token::ArgType::INT) {
            std::cout << std::setw(7) << "int" << " | "
                      << std::get<int>(cmd.arguments[i].value) << '\n';
        } else if (cmd.arguments[i].type == token::ArgType::STRING) {
            std::cout << std::setw(7) << "string" << " | "
                      << std::get<std::string>(cmd.arguments[i].value) << '\n';
        }
    }
  }
}