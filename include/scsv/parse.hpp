#pragma once
#include "scsv/detail/cast_and_assign.hpp"
#include "scsv/detail/for_range.hpp"
#include "scsv/detail/get_line.hpp"
#include "scsv/detail/missized_row_exception.hpp"
#include "scsv/detail/skip_header.hpp"
#include "scsv/detail/skip_trailing_caret_return.hpp"
#include "scsv/detail/split.hpp"
#include "scsv/options.hpp"

#include <istream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/pfr/core.hpp>
#include <magic_enum.hpp>

namespace scsv
{
    template<AnyOptions auto Opts = Options{}, typename Schema>
        requires std::is_aggregate_v<Schema>
    void parse(std::vector<Schema>& parsed, std::string_view data, char field_delim = ',',
               char lines_delim = '\n', char quote = '"')
    {
        std::array<std::string_view, boost::pfr::tuple_size_v<Schema>> fields;
        detail::skip_header<Opts>(data, lines_delim);
        while (!data.empty())
        {
            auto line = detail::get_line(data, lines_delim);
            detail::skip_trailing_caret_return<Opts>(line);
            detail::split(fields, line, field_delim, quote);
            parsed.emplace_back();
            detail::forRange<int, 0, boost::pfr::tuple_size_v<Schema>>(
                detail::castAndAssign(fields, parsed));
        }
    }
} // namespace scsv