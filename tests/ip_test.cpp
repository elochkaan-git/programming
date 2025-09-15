#include <gtest/gtest.h>
#include <vector>
#include "ip.hpp"

TEST(IP, splitIP) {
    std::vector<std::string> ips_s = {
        "192.168.0.1",
        "255.255.0.255",
        "0.0.0.0",
        "127.0.0.1"
    };

    std::vector<IP> ips;
    ips.reserve(ips_s.size());

    for(std::string& ip : ips_s)
        EXPECT_NO_THROW(ips.push_back(IP(ip)));
}