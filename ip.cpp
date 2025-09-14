#include "ip.hpp"
#include <iostream>

auto
IP::split(std::string& ip_) const
{
    int bytes[4] = {0, 0, 0, 0};
    short int ptr = 0;

    std::string temp_number = "";
    unsigned long i = 0;
    while(i != ip_.size()) {
        if (ip_.at(i) == '.') {
            bytes[ptr] = std::stoi(temp_number);
            ptr++;
            i++;
            temp_number = "";
        }
        else {
            temp_number.push_back(ip_.at(i));
            i++;
        }
    }

    return std::make_tuple(bytes[0], bytes[1], bytes[2], bytes[3]);
}

void
IP::print() const
{
    std::cout << std::get<0>(ip) << '.'
              << std::get<1>(ip) << '.'
              << std::get<2>(ip) << '.'
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
