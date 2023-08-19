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
        std::size_t initial_read = 3 * 1024;
        float read_scaling_factor = 1.5F;
    };

    template<typename Type>
    concept AnyOptions = std::same_as<Options, Type>;

} // namespace scsv