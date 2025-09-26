#include "ip.hpp"
#include <iostream>

auto
IP::split(std::string& ip) const
{
    int bytes[4] = {0, 0, 0, 0};
    short int ptr = 0;

    std::string temp_number = "";
    unsigned long i = 0;
    while(i != ip.size()) {
        if (ip.at(i) == '.') {
            bytes[ptr] = std::stoi(temp_number);
            ptr++;
            i++;
            temp_number = "";
        }
        else {
            temp_number.push_back(ip.at(i));
            i++;
        }
    }
    bytes[ptr] = std::stoi(temp_number);

    return std::make_tuple(bytes[0], bytes[1], bytes[2], bytes[3]);
}

void
IP::print() const
{
    std::cout << std::get<0>(ip_) << '.'
              << std::get<1>(ip_) << '.'
              << std::get<2>(ip_) << '.'
              << std::get<3>(ip_) << std::endl;
}

auto
IP::getIP() const -> decltype(ip_)
{
    return ip_;
}

IP::IP(std::string& ip)
{
    ip_ = split(ip);
}

IP::IP() {}
