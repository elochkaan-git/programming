#include "hash.hpp"

std::string hash(std::string word) {
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

void enrolled(std::string path) {
    std::ifstream input(path);
    std::string line, surname;
    unsigned long votes;

    while(std::getline(input, line)) {
        if(members.find(hash(line)) == members.end())
            members.insert({hash(line), line});
        else
            duplicates++;
    }
}

void unenrolled(std::string surname) {
    if(members.find(hash(surname)) == members.end())
        members.insert({hash(surname), surname});
    else
        duplicates++;
}

void end() {
    std::cout << '\n' << std::left << std::setfill('.') << std::setw(30) << "Total members" << members.size();
    std::cout << '\n' << std::string(31, '-') << '\n';
    for(const std::pair<std::string, std::string>& member : members) {
        std::cout << member.second << '\n';
    }

    std::cout << "\n\n" << std::left << std::setfill('.') << std::setw(30) << "Total duplicates" << duplicates;
}