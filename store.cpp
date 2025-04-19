#include "store.hpp"

HashTable::HashTable() {
    products.resize(10);
}

HashTable::HashTable(unsigned long long size) {
    products.resize(size);
}

std::string HashTable::hash(std::string word) {
    std::string secret = "1qkMuv0yQjHriLrUpPGuJXDaqgw6pzJl", result = "";
    if(word.length() < 32) word += secret.substr(0, 32 - word.length());
    else word += secret.substr(0, 3 - (word.length() % 3));

    for(size_t i = 2; i < word.length(); i += 2) {
        unsigned char b0 = word[0] ^ std::__rotl(word[i-2], result.length() % word.length());
        unsigned char b1 = word[1] ^ std::__rotl(word[i-1], result.length() % word.length());
        unsigned char b2 = word[2] ^ std::__rotl(word[i], result.length() % word.length());

        b0 %= 127;
        b1 %= 127;
        b2 %= 127;

        if(b0 < 33) b0 += 0x21;
        if(b1 < 33) b1 += 0x5B;
        if(b2 < 33) b2 += 0x36;

        result += b0;
        result += b1;
        result += b2;
    }

    return result;
}

void HashTable::insert(std::string name, unsigned long long price) {
    if(amount == products.size()) {
        products.push_back({hash(name), price});
        amount++;
    }
    else {
        products.at(amount) = {hash(name), price};
        amount++;
    }
}

void HashTable::remove(std::string name) {
    for(std::pair<std::string, unsigned long long>& each : products) {
        if(each.first == hash(name)) {
            unsigned long long pos = std::distance(products.begin(), std::find(products.begin(), products.end(), each));
            products.at(pos) = {"", 0};
            amount--;
            return;
        }
    }

    std::cout << "No such item!\n\n";
}

unsigned long long HashTable::find(std::string name) {
    for(const std::pair<std::string, unsigned long long>& each : products)
        if(each.first == hash(name))
            return each.second;
    return 0;
}

bool HashTable::is_empty() { return amount == 0 ? 1 : 0; }

unsigned long long HashTable::size() { return amount; }


