#include "ip.hpp"
#include <iostream>

auto
IP::split(std::string& ip_) const
{
    int bytes[4] = {0, 0, 0, 0};
    short int ptr = 0;

    unsigned long i = 0;
    while(i != std::string::npos) {
        std::string temp = ip_.substr(i == 0 ? 0 : i + 1, ip_.find('.', i + 1) - (i == 0 ? 0 : i + 1));
        bytes[ptr] = std::stoi(temp);
        ptr++;
        i = ip_.find('.', i + 1);
    }

    return std::make_tuple(bytes[0], bytes[1], bytes[2], bytes[3]);
}

void
IP::print() const
{
    std::cout << std::get<0>(ip) << ' '
              << std::get<1>(ip) << ' '
              << std::get<2>(ip) << ' '
              << std::get<3>(ip) << std::endl;
}

auto
IP::getIP() const -> decltype(ip)
{
    return ip;
}

IP::IP(std::string& ip_)
{
    ip = split(ip_);
}

IP::IP() {}
