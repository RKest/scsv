#pragma once

#include "scsv/detail/mmap_reading.hpp"
#include "scsv/parse.hpp"

namespace scsv
{
    template<typename Schema, AnyOptions auto Opts = Options{}>
        requires std::is_aggregate_v<Schema>
    auto parse_file(std::string_view path, char field_delim = ',', char line_delim = '\n')
        -> std::vector<Schema>
    {
        std::vector<Schema> parsed;
        for (auto data : detail::read_file_mmap(path, line_delim))
        {
            parse(parsed, data, field_delim, line_delim);
        }
        return parsed;
    }
} // namespace scsv