#include "tasks.hpp"

/* AUXILIARY FUNCTIONS */

std::vector<std::string> parse_equation(std::string equation) {
    int rb = 1; size_t firstSignPos;
    std::vector<std::string> result;
    while ((equation.find('+', rb) != std::string::npos) || (equation.find('-', rb) != std::string::npos)) {
        firstSignPos = std::min(equation.find('+', rb), equation.find('-', rb));
        result.push_back(equation.substr(rb-1, firstSignPos-rb+1));
        rb = firstSignPos+1;
    }
    if (equation.rfind('-') == std::string::npos) firstSignPos = equation.rfind('+');
    else if (equation.rfind('+') == std::string::npos) firstSignPos = equation.rfind('-');
    else firstSignPos = std::max(equation.rfind('+'), equation.rfind('-'));

    result.push_back(equation.substr(firstSignPos));
    return result;
}

std::string solve_expression(std::string expression) {
    long long b = 0;
    if(expression.find('(') != std::string::npos) {
        expression = expression.substr(1); 
        expression.pop_back();
    }
    if(expression[0] != '-' && expression[0] != '+') expression = '+' + expression;

    std::vector<std::string> members = parse_equation(expression);
    for(std::string& member : members) {
        b += std::stoll(member);
    }

    return b < 0 ? '-' + std::to_string(-b) : '+' + std::to_string(b);
}

/* SIMPLE EQUATIONS SOLVER */

std::string solve_equation(std::string equation) {
    std::string right_equation = equation.substr(0, equation.find('=')),
                left_equation = equation.substr(equation.find('=')+1);
    std::vector<std::string> right_members, left_members;
    long long k = 0, b = 0;

    if (right_equation[0] != '-') right_equation = '+' + right_equation;
    if (left_equation[0] != '-') left_equation = '+' + left_equation;

    right_members = parse_equation(right_equation);
    left_members = parse_equation(left_equation);

    for (std::string& member : right_members) {
        if (member.find('x') == std::string::npos)
            b += std::stoll(member);
        else {
            if (member[1] == 'x') member[1] = '1';
            else member.pop_back();
            k += std::stoll(member);
        }
    }
    for (std::string member : left_members) {
        if (member.find('x') == std::string::npos) 
            b -= std::stoll(member);
        else {
            if (member[1] == 'x') member[1] = '1';
            else member.pop_back();
            k -= std::stoll(member);
        }
    }

    if (k == 0 && b == 0) return "Infinite";
    else if (k == 0) return "NO"; 
    return "x="+std::to_string((-b)/k);
}

/* DELTA TIME FINDER */

long long what_time_is_it(std::vector<std::string> times) {
    long long timestamp = 0;
    std::vector<long long> timestamps(times.size(), 0);
    for (unsigned long i = 0; i < times.size(); ++i) {
        timestamp = (times[i][0] - '0') * 600 + 
                    (times[i][1] - '0') * 60 +
                    (times[i][3] - '0') * 10 +
                    (times[i][4] - '0');
        timestamps[i] = timestamp;
    }

    long long delta = LONG_LONG_MAX;
    for (unsigned long i = 0; i < timestamps.size(); ++i) {
        for (unsigned long j = i+1; j < timestamps.size(); ++j) {
            if (abs(timestamps[i] - timestamps[j]) <= 720) {
                if (abs(timestamps[i] - timestamps[j]) < delta)
                    delta = abs(timestamps[i] - timestamps[j]);
            }
            else if (abs(timestamps[i] - timestamps[j] - 1440) < delta)
                delta = abs(timestamps[i] - timestamps[j] - 1440);
        }
    }

    return delta;
}

/* PATH FINDING */

bool can_reach(long long fx, long long fy) {
    if (fx == 1 && fy == 1) return 1;
    else if (fx >= 1 && fy >= 1) {
        if (fx % 2 == 0) return can_reach(fx / 2, fy);
        if (fy % 2 == 0) return can_reach(fx, fy / 2);
        if (fx < fy) return can_reach(fx, fy+fx);
        if (fx > fy) return can_reach(fx+fy, fy);
    }
    else {
        if (fx < fy) return can_reach(fx+fy, fy);
        if (fx > fy) return can_reach(fx, fx+fy);
    }
    return false;
}

/* NO ONE */

unsigned long long no_one(unsigned long long n) {
    unsigned long long mask = 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000011;
    unsigned long long k = 0;
    bool fl = true;
    for (unsigned long long i = 0; i < n+1; ++i) {
        while (mask != 0) {
            if ((i & mask) == mask) {
                fl = false;
                break;
            }
            else {
                mask = (mask << 1);
                fl = true;
            }
        }
        if (fl) {
            k++; fl = false;
        }
        mask = 0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000011;
    }

    return k;
}

/* TOMATO PROTECTION */

std::set<std::pair<int, int>> tomato_protection(std::vector<std::vector<bool>> field) {
    std::set<std::pair<int, int>> bushes;
    // ub, db - номера строк
    // rb, lb - номера столбцов
    unsigned long ub = ULONG_MAX, lb = ULONG_MAX, db = 0, rb = 0;

    for(unsigned long r = 0; r < field.size(); ++r)
        for(unsigned long c = 0; c < field[0].size(); ++c)
            if(field[r][c]) {
                ub = std::min(r, ub);
                break;
            }

    for(unsigned long r = 0; r < field[0].size(); ++r)
        for(unsigned long c = 0; c < field.size(); ++c)
            if(field[c][r]) {
                lb = std::min(r, lb);
                break;
            }

    for(unsigned long r = 0; r < field.size(); ++r)
        for(unsigned long c = 0; c < field[0].size(); ++c)
            if(field[r][c]) {
                db = std::max(r, db);
                break;
            }

    for(unsigned long r = 0; r < field[0].size(); ++r)
        for(unsigned long c = 0; c < field.size(); ++c)
            if(field[c][r]) {
                rb = std::max(r, rb);
                break;
            }

    for(unsigned long c = 0; c < field[0].size(); ++c) {
        if(field[ub][c]) bushes.insert(std::pair<int, int>{ub, c});
        if(field[db][c]) bushes.insert(std::pair<int, int>{db, c});
    }
    for(unsigned long r = 0; r < field.size(); ++r) {
        if(field[r][rb]) bushes.insert(std::pair<int, int>{r, rb});
        if(field[r][lb]) bushes.insert(std::pair<int, int>{r, lb});
    }

    return bushes;
}

/* SIMPLE CALCULATOR */

long long calculator(std::string expression) {
    std::string temp, result;
    size_t left_p, right_p;

    expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
    if(expression[0] == '(') expression = '+' + expression;

    while (expression.find('(') != std::string::npos) {
        left_p = expression.rfind('(');
        right_p = expression.find(')', left_p);

        if(expression[left_p-1] == '(') {
            expression.insert(left_p, "+");
            right_p++; left_p++;
        }
        result = solve_expression(expression.substr(left_p, right_p-left_p+1));
        if(expression[left_p-1] == '-' && result[0] == '-') {
            result[0] = '+';
            expression.replace(left_p-1, right_p-left_p+2, result);
        }
        else if((expression[left_p-1] == '-' && result[0] == '+') || (expression[left_p-1] == '+' && result[0] == '-')) {
            result[0] = '-';
            expression.replace(left_p-1, right_p-left_p+2, result);
        }
        else expression.replace(left_p-1, right_p-left_p+2, result);
    }
    result = solve_expression(expression);
    expression.replace(0, expression.length(), result);

    return std::stoll(expression);
}