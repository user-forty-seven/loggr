#include "misc/info.hpp"
#include "misc/color.hpp"
#include "utils/utils.hpp"

#include <iostream>

using namespace color;

void info::show_info() {
    std::cout << BLUE << "loggr "  << YELLOW << "v1.0.0" << RESET << '\n'
              << CYAN << "Data stored at: " << utils::get_data_path() << RESET << '\n';
}