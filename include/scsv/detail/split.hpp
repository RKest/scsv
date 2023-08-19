#pragma once

#include "boost/algorithm/string.hpp"

namespace scsv::detail
{
    constexpr auto equal(char c)
    {
        return [c](char x)
        {
            return x == c;
        };
    }

    inline void split(std::vector<std::string>& result, std::string_view line, char delim)
    {
        boost::split(result, line, equal(delim));
    }
} // namespace scsv::detail