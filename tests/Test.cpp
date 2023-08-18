#include "scsv/parse.hpp"

#include "gtest/gtest.h"

TEST(SCSVTest, IgnoreTest)
{
    // given: any character
    constexpr char any_char = 'a';
    // given: a stream containing said character
    std::istringstream stream{"foobarbaz"};
    // when: ignoring up to the character
    scsv::detail::skip_header(stream, any_char);
    // then: the stream is at the character
    std::string rest;
    std::getline(stream, rest);
    EXPECT_EQ(rest, "rbaz");
}

struct ExampleSchema
{
    int a;
    float b;
    std::string c;
};

TEST(SCSVTest, ParseTest)
{
    // given: options where the header is not skipped
    constexpr auto options = []() -> scsv::Options
    {
        auto o = scsv::Options{};
        o.ignore_header = false;
        return o;
    }();
    // given: a stream containing a CSV
    std::istringstream stream{"1,2.0,three\n4,5.0,six\n"};
    // when: parsing the CSV
    auto const parsed = scsv::parse<ExampleSchema, options>(stream, ',', '\n');
    // then: the parsed data matches the CSV
    EXPECT_EQ(parsed.size(), 2);
    EXPECT_EQ(parsed[0].a, 1);
    EXPECT_FLOAT_EQ(parsed[0].b, 2.0f);
    EXPECT_EQ(parsed[0].c, "three");
    EXPECT_EQ(parsed[1].a, 4);
    EXPECT_FLOAT_EQ(parsed[1].b, 5.0f);
    EXPECT_EQ(parsed[1].c, "six");
}