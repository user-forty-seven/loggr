#include "core/models.hpp"
#include "parser/cli_lexer.hpp"
#include "parser/token.hpp"
#include "parser/cli_parser.hpp"
#include "errors/errors.hpp"
#include "core/dispatcher.hpp"

#include <iostream>

int main (int argc, char* argv[]) {
  // std::string test = "    this     is               a                test";
  // std::cout << "[BEFORE]: " << test << std::endl;
  // utils::normalize_whitespaces(test);
  // std::cout << "[AFTER]: " << test << std::endl;
  // models::Time time = utils::get_current_time();
  // std::cout << "[HOUR]: " << time.hour << std::endl;

  token::Command cmd = lexer::tokenize(argc, argv);
  // utils::print_tokens(cmd);
  models::ParsedCommand parsed_cmd;

  try {
    parsed_cmd = parser::parse(cmd);
  }
  catch(const errors::ParseError& e)  {
    std::cerr << e.full_message() << std::endl;
    return 1;
  }

  try {
    dispatcher::dispatch(parsed_cmd);
  }
  catch (const errors::TaskError& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const errors::CommandError& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const errors::ConfirmationError& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const errors::DataError& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  // loggr <command> [subcommand] [args...]
  return 0;
} 
