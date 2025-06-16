#pragma once

#include "core/models.hpp"

#include <string>
#include <nlohmann/json.hpp>

namespace manager {

    class TodoManager {
        public:
        TodoManager(const std::string &filename);
        void add_tool(const std::string &task);
        void list_tool(const models::FilterType& filter);
        void mark_tool(const int &n);
        void unmark_tool(const int &n);
        void delete_tool(const int &n);
        void clear_tool(const models::FilterType& filter);
        void edit_tool(const int &n, const std::string &task);
        private:
        std::string file;
        bool is_dulicate(const std::string &s, const nlohmann::json &j);
        void save(nlohmann::json &j, bool fix_ids=false);
        nlohmann::json load();
        void print_timestamp(const nlohmann::json &item, bool only_marked=false, bool only_unmarked=false);
        void truncate();
        void clear_marked();
    };

} // namespace manager