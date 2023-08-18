#pragma once

#include "scsv/options.hpp"

#include <istream>

namespace scsv::detail
{
    template<AnyOptions auto Opts = Options{}>
    void skip_header(std::istream& stream, Delimiter auto const& line_delim)
    {
        if constexpr (Opts.ignore_header)
        {
            while (!is_same(line_delim, stream.peek()))
            {
                stream.ignore();
            }
            stream.ignore();
        }
    }
} // namespace scsv::detail