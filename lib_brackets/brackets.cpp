#include "brackets.h"
#include "../lib_stack/stack.h"

#include <string>

bool check_same(char left, char right) {
    if (((left == '(') && (right == ')')) || ((left == '{') && (right == '}')) || ((left == '[') && (right == ']'))) {
        return true;
    }
    return false;
}

bool check_brackets(const std::string& toCheck) {
    Stack<char> stack(toCheck.length());
    if (toCheck[0] == ')' || toCheck[0] == ']' || toCheck[0] == '}') {
        return false;
    }
    if (toCheck[toCheck.length() - 1] == '(' || toCheck[toCheck.length() - 1] == '[' || toCheck[toCheck.length() - 1] == '{') {
        return false;
    }

    else {
        for (int i = 0; i < toCheck.length(); ++i) {
            char c = toCheck[i];
            
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            }
            else if (c == ')' || c == '}' || c == ']') {
                if (stack.is_empty()) {
                    return false;
                }
                
                char top = stack.top();
                stack.pop();
                
                if (!check_same(top, c)) {
                    return false;
                }
            }
        }

        return stack.is_empty();
    }
}
