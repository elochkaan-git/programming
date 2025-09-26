#pragma once

#include <string>

struct IP
{
private:
    std::tuple<int, int, int, int> ip_;

public:
    IP();
    IP(std::string& ip);
    auto split(std::string& ip) const;
    void print() const;
    auto getIP() const -> decltype(ip_);
};