#pragma once

namespace scsv
{
    namespace options
    {
    } // namespace options

    struct Options
    {
        bool ignore_header = true;
        bool strip_trailing_caret_return = true;
    };

    template<typename Type>
    concept AnyOptions = std::same_as<Options, Type>;

} // namespace scsv