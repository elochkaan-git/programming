#ifndef STORE_HPP
#define STORE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class HashTable {
    private:
        std::vector<std::pair<std::string, unsigned long long>> products;
        unsigned long long amount = 0;
        std::string hash(std::string word);

    public:
        HashTable();
        HashTable(unsigned long long size);
        void insert(std::string name, unsigned long long price);
        void remove(std::string name);
        unsigned long long find(std::string name);
        bool is_empty();
        unsigned long long size();
};

#endif