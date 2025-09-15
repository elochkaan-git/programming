#pragma once

#include <string>

struct IP
{
private:
    std::tuple<int, int, int, int> ip;

public:
    IP();
    IP(std::string& ip_);
    auto split(std::string& ip_) const;
    void print() const;
    auto getIP() const -> decltype(ip);
};