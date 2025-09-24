#include <gtest/gtest.h>
#include <fstream>
#include <regex>
#include <filesystem>

TEST(File, isFileExist) {
    ASSERT_TRUE(std::filesystem::exists("ip_filter.tsv"));
}

TEST(File, IsDataCorrect) {
    std::string line;
    std::ifstream in("ip_filer.tsv");
    const std::regex r(R"(\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\t\d+\t\d+\b)");
    while(std::getline(in, line)) {
        ASSERT_TRUE(std::regex_match(line.c_str(), r));
    }
}