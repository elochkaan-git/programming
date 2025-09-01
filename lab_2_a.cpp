#include "ip.hpp"
#include <algorithm>
#include <vector>
#include <fstream>

bool
compare(IP& a, IP& b)
{   
    decltype(auto) a_ip = a.getIP();
    decltype(auto) b_ip = b.getIP();

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
    
    std::sort(ips.begin(), ips.end(), compare);
    for(IP& ip : ips) ip.print();
}