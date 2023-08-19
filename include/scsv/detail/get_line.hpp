#pragma once

#include <string_view>

namespace scsv::detail
{
    constexpr auto get_line(std::string_view& data, char line_delim) -> std::string_view
    {
        auto end = data.find(line_delim);
        auto ret = data.substr(0, end);
        data.remove_prefix(end + 1);
        return ret;
    }
} // namespace scsv::detail