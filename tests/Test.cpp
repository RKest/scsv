#include "scsv/parse.hpp"
#include "scsv/parse_file.hpp"

#include "gtest/gtest.h"

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
    std::string_view data{"1,2.0,three\n4,5.0,six\n"};
    // when: parsing the CSV
    std::vector<ExampleSchema> parsed;
    scsv::parse<options>(parsed, data, ',', '\n');
    // then: the parsed data matches the CSV
    EXPECT_EQ(parsed.size(), 2);
    EXPECT_EQ(parsed[0].a, 1);
    EXPECT_FLOAT_EQ(parsed[0].b, 2.0f);
    EXPECT_EQ(parsed[0].c, "three");
    EXPECT_EQ(parsed[1].a, 4);
    EXPECT_FLOAT_EQ(parsed[1].b, 5.0f);
    EXPECT_EQ(parsed[1].c, "six");
}