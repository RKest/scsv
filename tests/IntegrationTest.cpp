#include "scsv/parse_file.hpp"

#include "gtest/gtest.h"

struct IntegrationSchema
{
    int year;
    std::string industry_code_ANZSIC;
    std::string industry_name_ANZSIC;
    std::string rme_size_grp;
    std::string variable;
    std::string value;
    std::string unit;
};

TEST(File, Integration)
{
    // given: Path to csv file
    constexpr auto csv_path = "test.csv";
    // when: parsing the CSV
    auto const parsed = scsv::parse_file<IntegrationSchema>(csv_path);
    // then: First element matches value in dataset
    EXPECT_EQ(parsed[0].year, 2011);
    EXPECT_EQ(parsed[0].industry_code_ANZSIC, "A");
    EXPECT_EQ(parsed[0].industry_name_ANZSIC, "Agriculture Forestry and Fishing");
    EXPECT_EQ(parsed[0].rme_size_grp, "a_0");
    EXPECT_EQ(parsed[0].variable, "Activity unit");
    EXPECT_EQ(parsed[0].value, "46134");
    EXPECT_EQ(parsed[0].unit, "COUNT\r");
}