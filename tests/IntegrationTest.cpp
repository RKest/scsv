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
    std::vector<IntegrationSchema> parsed;
    // when: parsing the CSV
    try
    {
        parsed = scsv::parse_file<IntegrationSchema>(csv_path);
    }
    catch (const std::system_error& e)
    {
        std::cerr << "In order to run integration tests tests tests, download a test.csv from "
                     "`https://www.stats.govt.nz/assets/Uploads/Annual-enterprise-survey/"
                     "Annual-enterprise-survey-2021-financial-year-provisional/Download-data/"
                     "annual-enterprise-survey-2021-financial-year-provisional-size-bands-csv.csv` "
                     "and rename it to `test.csv` in the PROJECT_SOURCE_DIR\n";
        FAIL();
    }
    // then: First element matches value in dataset
    EXPECT_EQ(parsed.front().year, 2011);
    EXPECT_EQ(parsed.front().industry_code_ANZSIC, "A");
    EXPECT_EQ(parsed.front().industry_name_ANZSIC, "\"Agriculture, Forestry and Fishing\"");
    EXPECT_EQ(parsed.front().rme_size_grp, "a_0");
    EXPECT_EQ(parsed.front().variable, "Activity unit");
    EXPECT_EQ(parsed.front().value, "46134");
    EXPECT_EQ(parsed.front().unit, "COUNT");
    // then: Last element matches value in dataset
    EXPECT_EQ(parsed.back().year, 2021);
    EXPECT_EQ(parsed.back().industry_code_ANZSIC, "all");
    EXPECT_EQ(parsed.back().industry_name_ANZSIC, "All Industries");
    EXPECT_EQ(parsed.back().rme_size_grp, "j_Grand_Total");
    EXPECT_EQ(parsed.back().variable, "Fixed tangible assets");
    EXPECT_EQ(parsed.back().value, "591351");
    EXPECT_EQ(parsed.back().unit, "DOLLARS(millions)");
}