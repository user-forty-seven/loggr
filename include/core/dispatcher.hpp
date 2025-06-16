#pragma once

#include "core/models.hpp"

namespace dispatcher {
    void dispatch(const models::ParsedCommand& cmd);
} // namespace dispatcher