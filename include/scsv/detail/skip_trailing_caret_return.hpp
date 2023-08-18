#pragma once

#include <string>

namespace scsv::detail
{
    template<AnyOptions auto Opts> void skip_trailing_caret_return(std::string& line)
    {
        if constexpr (Opts.strip_trailing_caret_return)
        {
            if (line.back() == '\n') { line.pop_back(); }
        }
    }
} // namespace scsv::detail