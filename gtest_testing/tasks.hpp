#ifndef TASKS_HPP
#define TASKS_HPP

#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <climits>
#include <cstddef>
#include <utility>


std::string solve_equation(std::string);
long long what_time_is_it(std::vector<std::string>);
bool can_reach(long long, long long);
unsigned long long no_one(unsigned long long);
std::set<std::pair<int, int>> tomato_protection(std::vector<std::vector<bool>>);
long long calculator(std::string);

#endif