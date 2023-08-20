#pragma once

#include "scsv/detail/missized_row_exception.hpp"

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

    template<std::size_t IntoSize>
    constexpr void split(std::array<std::string_view, IntoSize>& out, std::string_view row,
                         char field_delim, char quote)
    {
        std::size_t size = 0, next = 0, i = 0;
        bool in_quote = false;
        for (; i + size < row.size(); ++size)
        {
            in_quote ^= row[i + size] == quote;
            if (!in_quote && row[i + size] == field_delim)
            {
                if (next < IntoSize - 1) { out[next] = row.substr(i, size); }
                ++next;
                i += size + 1;
                size = -1;
            }
        }
        if (next != IntoSize - 1) { throw missized_row_exception(IntoSize, next + 1); }
        out[next] = row.substr(i, size);
    }
} // namespace scsv::detail