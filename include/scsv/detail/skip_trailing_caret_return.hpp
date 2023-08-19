#pragma once

#include <string>

namespace scsv::detail
{
    template<AnyOptions auto Opts> void skip_trailing_caret_return(std::string_view& line)
    {
        if constexpr (Opts.strip_trailing_caret_return)
        {
            if (line.back() == '\n') { line.remove_suffix(1); }
        }
    }
} // namespace scsv::detail