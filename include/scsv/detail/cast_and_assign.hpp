#pragma once

#include <optional>

#include "boost/lexical_cast.hpp"
#include "boost/pfr/core.hpp"

namespace scsv::detail
{
    template<typename Type>
    concept Optional = requires(Type value) {
        []<typename T>(std::optional<T>& opt) {
        }(value);
    };

    template<int I, std::size_t Size, Optional Type>
    constexpr void assign(Type& assign_to, const std::array<std::string_view, Size>& split)
    {
        assign_to = boost::lexical_cast<typename Type::value_type>(split[I]);
    }

    template<int I, std::size_t Size, typename Type>
    constexpr void assign(Type& assign_to, const std::array<std::string_view, Size>& split)
    {
        assign_to = boost::lexical_cast<Type>(split[I]);
    }

    template<typename Schema, std::size_t Size>
    auto castAndAssign(const std::array<std::string_view, Size>& split, std::vector<Schema>& result)
    {
        return [&split, &result]<int I>(std::integral_constant<int, I>)
        {
            if (!split[I].empty())
            {
                auto& assign_to = boost::pfr::get<I>(result.back());
                assign<I>(assign_to, split);
                return;
            }
        };
    }

} // namespace scsv::detail