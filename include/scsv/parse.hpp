#include "scsv/detail/cast_and_assign.hpp"
#include "scsv/detail/delimiter.hpp"
#include "scsv/detail/for_range.hpp"
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
    template<typename Schema, AnyOptions auto Opts = Options{}>
        requires std::is_aggregate_v<Schema>
    auto parse(std::istream& stream, detail::Delimiter auto const& fields_delim,
               detail::Delimiter auto const& lines_delim) -> std::vector<Schema>
    {
        std::vector<Schema> parsed;
        std::vector<std::string> fields;
        detail::skip_header<Opts>(stream, lines_delim);
        for (std::string line; std::getline(stream, line);)
        {
            detail::skip_trailing_caret_return<Opts>(line);
            detail::split(fields, line, fields_delim);
            parsed.emplace_back();
            detail::forRange<int, 0, boost::pfr::tuple_size_v<Schema>>(
                detail::castAndAssign(fields, parsed));
            fields.clear();
        }
        return parsed;
    }
} // namespace scsv