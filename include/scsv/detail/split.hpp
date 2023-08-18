#pragma once

#include "scsv/detail/delimiter.hpp"

#include "boost/algorithm/string.hpp"

namespace scsv::detail
{
    void split(std::vector<std::string>& result, std::string const& line,
               Delimiter auto const& delim)
    {
        if constexpr (requires {
                          boost::split(result, line, boost::is_any_of(std::string{&delim, 1}));
                      })
        {
            boost::split(result, line, boost::is_any_of(std::string{&delim, 1}));
        }
        else if constexpr (requires { boost::split(result, line, delim); })
        {
            boost::split(result, line, delim);
        }
        else { assert(0 && "Delimiter type is not supported"); }
    }
} // namespace scsv::detail