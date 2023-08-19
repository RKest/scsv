#include "gtest/gtest.h"

#include "scsv/detail/mmap_reading.hpp"

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <fstream>

// Because pushing to the vector skewes benchmark results, to check if everything works properly
// this #define needs to be uncommented
// #define CHECK_IF_WORKS_PROPERLY

TEST(Bench, Mark)
{
    std::vector<std::string> istream_lines;
    std::vector<std::string> chunked_lines;
    std::vector<std::string> one_read_lines;
    constexpr static auto csv_path = "test.csv";
    ankerl::nanobench::Bench().run("i-streams bench",
                                   [&]()
                                   {
                                       std::ifstream stream{csv_path};
                                       std::string s;
                                       while (std::getline(stream, s))
                                       {
#ifdef CHECK_IF_WORKS_PROPERLY
                                           istream_lines.push_back(s);
#endif
                                           ankerl::nanobench::doNotOptimizeAway(s);
                                       }
                                   });

    ankerl::nanobench::Bench().run("chunked read",
                                   [&]()
                                   {
                                       for (auto s : scsv::detail::read_file_mmap(csv_path, '\n'))
                                       {
                                           while (!s.empty())
                                           {
                                               auto const pos = s.find('\n');
                                               auto const line = s.substr(0, pos);
                                               s.remove_prefix(pos + 1);
                                               ankerl::nanobench::doNotOptimizeAway(line);
#ifdef CHECK_IF_WORKS_PROPERLY
                                               chunked_lines.emplace_back(line);
#endif
                                           }
                                       }
                                   });
    ankerl::nanobench::Bench().run("one read",
                                   [&]()
                                   {
                                       auto const mmap = mio::mmap_source(csv_path);
                                       std::string_view s{mmap.data(), mmap.size()};
                                       while (!s.empty())
                                       {
                                           auto const pos = s.find('\n');
                                           auto const line = s.substr(0, pos);
                                           s.remove_prefix(pos + 1);
                                           ankerl::nanobench::doNotOptimizeAway(line);
#ifdef CHECK_IF_WORKS_PROPERLY
                                           one_read_lines.emplace_back(line);
#endif
                                       }
                                   });
    EXPECT_EQ(istream_lines, chunked_lines);
    EXPECT_EQ(one_read_lines, chunked_lines);
}