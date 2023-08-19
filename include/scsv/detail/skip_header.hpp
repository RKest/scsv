#pragma once

#include "scsv/options.hpp"

#include <string_view>

namespace scsv::detail
{
    template<AnyOptions auto Opts = Options{}>
    void skip_header(std::string_view& stream, char line_delim)
    {
        if constexpr (Opts.ignore_header) { stream.remove_prefix(stream.find(line_delim) + 1); }
    }
} // namespace scsv::detail