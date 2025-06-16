#pragma once
#include "parser/token.hpp"

namespace models {

    struct Time {
        int year;
        int month;
        std::string month_name;
        int day;
        int hour;
        int minute;
        int second;
    };


    enum class FilterType {
        NONE,
        MARKED,
        UNMARKED,
        ALL
    };

    struct ParsedCommand {
        token::ActionType type;
        token::SubType subtype;
        int task_id = -1; // default
        std::string task_description = ""; // default
        FilterType filter = FilterType::NONE; // ex, for list: "marked" and "unmarked" and for clear, "all" and "completed"
    };

} // namespace models