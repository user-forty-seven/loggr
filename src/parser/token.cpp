#include "parser/token.hpp"
#include <unordered_map>
#include <string>

namespace token {

   const std::unordered_map<std::string, ActionType> action_map = {
    {"add", ActionType::ADD},
    {"edit", ActionType::EDIT},
    {"remove", ActionType::REMOVE},
    {"clear", ActionType::CLEAR},
    {"list", ActionType::LIST},
    {"mark", ActionType::MARK},
    {"unmark", ActionType::UNMARK},
    {"help", ActionType::HELP},
    {"info", ActionType::INFO},
    {"UNKNOWN", ActionType::UNKNOWN},
    {"NONE", ActionType::NONE}
  };

  const std::unordered_map<std::string, SubType> subaction_map = {
    {"task", SubType::TASK},
    {"tasks", SubType::TASKS},
    {"UNKNOWN", SubType::UNKNOWN},
    {"NONE", SubType::NONE}
  };

  const std::unordered_map<ActionType, std::string> action_map_reverse = {
    {ActionType::ADD,"add"},
    {ActionType::EDIT,"edit"},
    {ActionType::REMOVE,"remove"},
    {ActionType::CLEAR,"clear"},
    {ActionType::LIST,"list"},
    {ActionType::MARK,"mark"},
    {ActionType::UNMARK,"unmark"},
    {ActionType::HELP,"help"},
    {ActionType::INFO,"info"},
    {ActionType::UNKNOWN,"UNKNOWN"},
    {ActionType::NONE, "NONE"}
  };

  const std::unordered_map<SubType, std::string> subaction_map_reverse = {
    {SubType::TASK,"task"},
    {SubType::TASKS,"tasks"},
    {SubType::UNKNOWN,"UNKNOWN"},
    {SubType::NONE, "NONE"}
  };
}
