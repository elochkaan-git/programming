#include "../tasks.hpp"

TEST(TestEquationSolver, RandomValues) {
    ASSERT_EQ(solve_equation("1+x=2"), "x=1");
    ASSERT_EQ(solve_equation("x+2x+1-2=6+x-1"), "x=3");
    ASSERT_EQ(solve_equation("x+0+0+0+0+0+0+0+0=0"), "x=0");
    ASSERT_EQ(solve_equation("-1-2-3-4-5-6-7-8-9-x=80"), "x=-125");
}

TEST(TestEquationSolver, NoSolutions) {
    ASSERT_EQ(solve_equation("x-x=1"), "NO");
    ASSERT_EQ(solve_equation("x+2x+3x+4x=10x+1"), "NO");
    ASSERT_EQ(solve_equation("0=1"), "NO");
}

TEST(TestEquationSolver, InfiniteSolutions) {
    ASSERT_EQ(solve_equation("x=x"), "Infinite");
    ASSERT_EQ(solve_equation("x+2x+3x+4x=10x"), "Infinite");
    ASSERT_EQ(solve_equation("4x-10+15+x=x+x+x+x+x+100-95"), "Infinite");
}


TEST(TestMinDeltaFinder, RandomTimes) {
    ASSERT_EQ(what_time_is_it(std::vector<std::string>{
        "08:15", "12:45", "16:30", "23:59", "00:00",
        "09:05", "14:20", "19:50", "03:33", "07:11",
        "10:10", "15:40", "20:25", "01:02", "05:55",
        "11:11", "17:35", "22:00", "04:44", "06:22"
    }), 1);
    ASSERT_EQ(what_time_is_it(std::vector<std::string>{"01:00", "01:00"}), 0);
    ASSERT_EQ(what_time_is_it(std::vector<std::string>{
        "01:00", "01:05", "01:10", "01:15", "01:20", 
        "02:00", "02:30", "03:00", "03:30", "04:00"}), 
        5);
    ASSERT_EQ(what_time_is_it(std::vector<std::string>{"23:59", "11:59"}), 720);
}


TEST(TestPathFinding, RandomValues) {
    ASSERT_EQ(can_reach(2, 0), true);
    ASSERT_EQ(can_reach(4, 10), true);
    ASSERT_EQ(can_reach(36, 28), true);
    ASSERT_EQ(can_reach(2, 2), true);
}

TEST(TestPathFinding, IncorrectValue) {
    ASSERT_EQ(can_reach(3, 3), false);
    ASSERT_EQ(can_reach(3, 0), false);
    ASSERT_EQ(can_reach(0, 5), false);
    ASSERT_EQ(can_reach(0, 0), false);
}


TEST(TestOneCounter, RandomValues) {
    ASSERT_EQ(no_one(5), 5);
    ASSERT_EQ(no_one(10), 8);
    ASSERT_EQ(no_one(100), 34);
    ASSERT_EQ(no_one(1), 2);
}


TEST(TestTomatoProtection, RandomValues) {
    std::set<std::pair<int, int>> test = {
        std::pair<int, int>{1, 2}, std::pair<int, int>{1, 3},
        std::pair<int, int>{1, 4}, std::pair<int, int>{1, 5},
        std::pair<int, int>{1, 6}, std::pair<int, int>{2, 9},
        std::pair<int, int>{1, 7}, std::pair<int, int>{3, 9},
        std::pair<int, int>{1, 8}, std::pair<int, int>{5, 9},
        std::pair<int, int>{1, 9}, std::pair<int, int>{7, 9},
        std::pair<int, int>{3, 2}, std::pair<int, int>{8, 9},
        std::pair<int, int>{4, 2}, std::pair<int, int>{8, 4},
        std::pair<int, int>{6, 2}, std::pair<int, int>{8, 5},
        std::pair<int, int>{7, 2}, std::pair<int, int>{8, 7},
        std::pair<int, int>{8, 3}, std::pair<int, int>{8, 8}
    };
    ASSERT_EQ(tomato_protection(std::vector<std::vector<bool>>{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }), test);

    test = {
        std::pair<int, int>{1, 1}, std::pair<int, int>{5, 2},
        std::pair<int, int>{1, 2}, std::pair<int, int>{5, 3},
        std::pair<int, int>{1, 3}, std::pair<int, int>{5, 4},
        std::pair<int, int>{1, 4}, std::pair<int, int>{5, 5},
        std::pair<int, int>{1, 5}, std::pair<int, int>{2, 5},
        std::pair<int, int>{5, 1}, std::pair<int, int>{4, 1}
    };
    ASSERT_EQ(tomato_protection(std::vector<std::vector<bool>>{
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    }), test);

    test = {
        std::pair<int, int>{1, 1}
    };
    ASSERT_EQ(tomato_protection(std::vector<std::vector<bool>>{
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    }), test);
}


TEST(TestCalculator, NoBrackets) {
    ASSERT_EQ(calculator("1+1"), 2);
    ASSERT_EQ(calculator("-1-1"), -2);
    ASSERT_EQ(calculator("1-1"), 0);
    ASSERT_EQ(calculator("-1+1"), 0);
}

TEST(TestCalculator, OnePairBrackets) {
    ASSERT_EQ(calculator("-(1+1)"), -2);
    ASSERT_EQ(calculator("1+2+3+(4+5+6-7-8-9+10+11+12)-13-14-15"), -12);
}

TEST(TestCalculator, TwoPairBrackets) {
    ASSERT_EQ(calculator("-(-(1+2+3)-(1+2-4))"), 5);
    ASSERT_EQ(calculator("-((1+2+3)-(1+2-4))"), -7);
}

TEST(TestCalculator, ManyPairBrackets) {
    ASSERT_EQ(calculator("((((((((1+2)-3)+4)-5)+6)-7)+8)-9)+10"), 7);
}

TEST(TestCalculator, RemoveSpaces) {
    ASSERT_EQ(calculator("  1    + 1   "), 2);
    ASSERT_EQ(calculator("-1 -1   "), -2);
    ASSERT_EQ(calculator("-( - ( 1+ 2 + 3 )  - (1 + 2 - 4 ) ) "), 5);
    ASSERT_EQ(calculator("     - ( ( 1+ 2 +3)-(1+2-4     ) )"), -7);
    ASSERT_EQ(calculator("(( ( ( ( ( ( (1  +2)-3   )+4) - 5)+ 6)- 7) +8 ) -  9   )+10"), 7);
}
