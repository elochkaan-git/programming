#include "ip.hpp"
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

bool
compare(IP& a, IP& b)
{   
    const auto& a_ip = a.getIP();
    const auto& b_ip = b.getIP();

    return a_ip > b_ip;
}

int
main()
{   
    std::vector<IP> ips(1000);

    std::string line; int i = 0;
    std::ifstream in("ip_filter.tsv");
    while(std::getline(in, line)) {
        std::string temp = line.substr(0, line.find('\t')); 
        ips.at(i) = IP(temp);
        i++;
    }
    
    auto isFirstByteEqualOne = [](IP& a) -> bool{
        return std::get<0>(a.getIP()) == 1;
    };

    auto is46and70 = [](IP& a) -> bool{
        const auto& a_ip = a.getIP();
        return std::get<0>(a_ip) == 46 && std::get<1>(a_ip) == 70;
    };

    auto is46any = [](IP& a) -> bool{
        const auto& a_ip = a.getIP();
        return std::get<0>(a_ip) == 46 ||
               std::get<1>(a_ip) == 46 ||
               std::get<2>(a_ip) == 46 ||
               std::get<3>(a_ip) == 46;
    };

    std::sort(ips.begin(), ips.end(), compare);
    for(IP& ip : ips) ip.print();
    std::cout << "==========================================\n";

    for(IP& ip : ips) if (isFirstByteEqualOne(ip)) ip.print();
    std::cout << "==========================================\n";

    for(IP& ip : ips) if (is46and70(ip)) ip.print();
    std::cout << "==========================================\n";

    for(IP& ip : ips) if (is46any(ip)) ip.print();
    std::cout << "==========================================\n";
}