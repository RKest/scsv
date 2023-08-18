#pragma once

#include <concepts>
#include <string_view>

namespace scsv::detail
{
    template<typename Type>
    concept Delimiter = std::same_as<char, Type> || requires(Type value) {
        {
            value(std::declval<std::string_view>())
        } -> std::same_as<bool>;
    };

    constexpr auto is_same(Delimiter auto const& delim, char c)
    {
        if constexpr (requires { delim == c; })
        {
            return delim == c;
        }
        else
        {
            return delim(std::string_view{&c, 1});
        }
    }
}