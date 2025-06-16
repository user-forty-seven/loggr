#pragma once
#include <vector>
#include <variant>
#include <string>
#include <unordered_map>

namespace token {
  enum class ActionType {
    ADD,
    EDIT,
    REMOVE,
    CLEAR,
    LIST,
    MARK,
    UNMARK,
    HELP,
    INFO,
    UNKNOWN,
    NONE
  };
  
  enum class SubType {
    TASK,
    TASKS,
    UNKNOWN,
    NONE
  };

  enum class ArgType {
    INT, // for ids
    STRING // for strings
  };
  
  struct Arg {
    ArgType type; 
    std::variant<std::string, int> value; // int for ids and strings for other stuff
  };

  struct Command {
    ActionType type;
    SubType subtype;
    std::vector<Arg> arguments;
    std::unordered_map<std::string, std::string> flags; // future plan maybe? like --ouput json and other sutff
  };

  extern const std::unordered_map<std::string, ActionType> action_map;
  extern const std::unordered_map<ActionType, std::string> action_map_reverse;
  extern const std::unordered_map<std::string, SubType> subaction_map;
  extern const std::unordered_map<SubType, std::string> subaction_map_reverse;
}
