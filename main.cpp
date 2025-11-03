#include "core/models.hpp"
#include "parser/cli_lexer.hpp"
#include "parser/token.hpp"
#include "parser/cli_parser.hpp"
#include "errors/errors.hpp"
#include "core/dispatcher.hpp"

#include <iostream>

int main (int argc, char* argv[]) {
  token::Command cmd = lexer::tokenize(argc, argv);
  models::ParsedCommand parsed_cmd;

  try {
    parsed_cmd = parser::parse(cmd);
    dispatcher::dispatch(parsed_cmd);
  }
  catch(const errors::ParseError& e)  {
    std::cerr << e.full_message() << std::endl;
    return 1;
  }
  catch(const errors::LoggrError& e)  { // catches TaskError, CommandError, DataError, ConfirmationError
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
} 
