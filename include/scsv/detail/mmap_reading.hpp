#pragma once

#include "scsv/3rdparty/__generator.hpp"
#include "scsv/options.hpp"

#include <mio/mmap.hpp>

namespace scsv::detail
{
    template<AnyOptions auto Opts = Options{}>
    [[nodiscard]] auto read_file_mmap(std::string_view path, char line_terminator)
        -> std::generator<std::string_view>
    {
        std::size_t offset = 0;
        std::size_t read_size = Opts.initial_read;
        while (true)
        {
            mio::mmap_source mmap{path, offset, read_size};
            std::string_view s{mmap.data(), mmap.size()};
            auto end = s.rfind(line_terminator) + 1;
            co_yield s.substr(0, end);
            offset += end;
            if (mmap.size() < offset)
            {
                mio::mmap_source mmap{path, offset, mio::map_entire_file};
                co_yield std::string_view{mmap.data(), mmap.size()};
                break;
            }
            read_size *= Opts.read_scaling_factor;
        }
    }
} // namespace scsv::detail