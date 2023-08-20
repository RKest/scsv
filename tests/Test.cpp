#include "scsv/parse.hpp"
#include "scsv/parse_file.hpp"

#include "gmock/gmock-more-matchers.h"
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

TEST(SCVTest, SplitTest)
{
    // given: Example CSV row data
    const auto example_data = "1,2.0,three,'Hello, World'";

    // when: Splitting the row
    std::array<std::string_view, 4> result;
    scsv::detail::split(result, example_data, ',', '\'');

    // then: Fields are split correctly
    EXPECT_EQ(result[0], "1");
    EXPECT_EQ(result[1], "2.0");
    EXPECT_EQ(result[2], "three");
    EXPECT_EQ(result[3], "'Hello, World'");
}

struct SCSVThrowingTest : testing::TestWithParam<std::pair<std::string_view, std::string_view>>
{
};

TEST_P(SCSVThrowingTest, ShouldThrowWithMessage)
{
    // given: Example CSV row data
    const auto [example_data, expected_message] = GetParam();

    std::array<std::string_view, 4> result;
    // when: Splitting the row
    EXPECT_THAT([&]() { return scsv::detail::split(result, example_data, ',', '`'); },
                testing::ThrowsMessage<scsv::missized_row_exception>(expected_message));
}

std::vector<SCSVThrowingTest::ParamType> test_cases{
    {"1,2.0,`Hello, World`", "Expected row containing `4` fields, but got `3` fields."},
    {"1,2.0,three,`Hello, World`,five", "Expected row containing `4` fields, but got `5` fields."},
    {"1,2,3,4,5,6,7,8,9,10,11,12,13,14,15",
     "Expected row containing `4` fields, but got `15` fields."},
};

INSTANTIATE_TEST_SUITE_P(, SCSVThrowingTest,
                         testing::ValuesIn(test_cases

                                           ));