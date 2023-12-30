#include <iostream>
#include <string>
#include <cctype>

std::string::const_iterator iter;

int expression();

int number() {
    if (!isdigit(*iter)) {
        throw std::runtime_error("Expected a number");
    }
    int result = *iter - '0';
    ++iter;
    return result;
}

int factor() {
    if (*iter == '(') {
        ++iter; // Skip '('
        int result = expression();
        if (*iter != ')') {
            throw std::runtime_error("Expected ')'");
        }
        ++iter; // Skip ')'
        return result;
    } else {
        return number();
    }
}

int term() {
    int result = factor();
    while (*iter == '*' || *iter == '/') {
        if (*iter == '*') {
            ++iter;
            result *= factor();
        } else {
            ++iter;
            result /= factor();
        }
    }
    return result;
}

int expression() {
    int result = term();
    while (*iter == '+' || *iter == '-') {
        if (*iter == '+') {
            ++iter;
            result += term();
        } else {
            ++iter;
            result -= term();
        }
    }
    return result;
}

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        iter = s.begin();
        try {
            std::cout << expression() << std::endl;
            if (iter != s.end()) {
                throw std::runtime_error("Unexpected characters at the end of the expression");
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}
