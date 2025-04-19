#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include <bit>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>

extern std::map<std::string, std::string> members;
extern unsigned long duplicates;

std::string hash(std::string word);
void enrolled(std::string path);
void unenrolled(std::string surname);
void end();

#endif