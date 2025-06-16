#pragma once
#include "core/models.hpp"
#include "parser/token.hpp"
#include <string>

namespace utils {

    std::string get_data_path();
    void normalize_whitespaces(std::string &s);
    models::Time get_current_time();
    void print_tokens(const token::Command& cmd);

} // namespace utils