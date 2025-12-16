#include "../expression/expression.h"
#include "../lib_brackets/brackets.h"

#include "parser.h"

#include <cctype>
#include <string>
#include <cmath>
#include <stdexcept>

namespace {
// Проверка символа на оператор
    bool isOperator(char c);
    
    // Проверка символа на скобку
    bool isBracket(char c);

    // Проверка символа на модуль
    bool isModule(char c);
    
    // Проверка символа на часть числа
    bool isDigit(char c);
    
    // Получение приоритета оператора
    int getPriority(const std::string& op);
    
    // Создание лексемы-оператора
    Lexem createOperatorLexem(char op);
    
    // Создание лексемы-числа
    Lexem createNumberLexem(const std::string& numStr);
    
    // Создание лексемы-функции
    Lexem createFunctionLexem(const std::string& funcName);
    
    // Создание лексемы-скобки
    Lexem createBracketLexem(char bracket);
    
    // Создание лексемы-переменной
    Lexem createVariableLexem(const std::string& varName);
    
    // Проверка корректности имени переменной
    bool isValidVariableName(const std::string& name);
}

namespace Parser {
    List<Lexem> parse(const std::string& expression) {
        //! @todo Сделать проверку скобок в начале
        size_t j = 0;
        std::string toCheckBrackets = "";
        const size_t length = expression.length();
        while (j < length) {
            const char current = expression[j];
            if (isBracket(current) || isModule(current)) {
                toCheckBrackets += expression[j];
            }
            ++j;
        }

        if (!check_brackets(toCheckBrackets)) {
            std::logic_error("Brackets are wrong!");
        }


        List<Lexem> result;
        size_t i = 0;
        
        while (i < length) {
            const char current = expression[i];
            
            // Обработка чисел
            if (isDigit(current)) {
                std::string numStr;
                
                while (i < length && isDigit(expression[i])) {
                    numStr += expression[i];
                    ++i;
                }
                
                result.push_back(createNumberLexem(numStr));
                //! @todo если в одном месте - потом поменять на строки, убрать функцию
                continue;
            }
            
            // Обработка функций и переменных
            if (std::isalpha(current) || current == '_') {
                std::string name;
                while (i < length && (std::isalpha(expression[i]) || expression[i] == '_' || isDigit(expression[i]))) {
                    name += expression[i];
                    ++i;
                }
                
                // Проверяем, функция ли это
                if (name == "sin" || name == "cos" || name == "tg") {
                    result.push_back(createFunctionLexem(name));
                }
                else if (isValidVariableName(name)) {
                    // Переменная
                    result.push_back(createVariableLexem(name));
                }
                else {
                    //! @todo ERROR
                }
                continue;
            }
            
            // Обработка операторов
            if (isOperator(current)) {
                // Обработка унарного минуса
                if (current == '-') {
                    // Унарный минус может обрабатываться только когда он задан в виде (- что-то)
                    if (result.tail()->_value.type == OPEN_BRACKET ||
                        result.tail()->_value.type == MODULE) { 
                        // Надо добавить (0 - следующий)
                        result.push_back(createNumberLexem("0"));
                    }
                }
                
                result.push_back(createOperatorLexem(current));
                ++i;
                continue;
            }
            
            // Обработка скобок
            if (isBracket(current)) {
                result.push_back(createBracketLexem(current));
                ++i;
                continue;
            }

            //! @todo обработка ошибки
        }
        
        return result;
    }
}


namespace {

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    
    bool isBracket(char c) {
        return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
    }

    bool isModule(char c) {
        return c == '|';
    }
    
    bool isDigit(char c) {
        return (c >= '0' && c <= '9');
    }
    
    int getPriority(const std::string& op) {
        if (op == "^") return 3;
        if (op == "*" || op == "/") return 2;
        if (op == "+" || op == "-") return 1;
        return 0;
    }
    
    Lexem createOperatorLexem(char op) {
        std::string opStr(1, op);
        return Lexem(opStr, OPERATOR, 0, nullptr, getPriority(opStr));
    }
    
    Lexem createNumberLexem(const std::string& numStr) {
        const double value = std::stod(numStr);
        return Lexem(numStr, NUMBER, value);
    }
    
    Lexem createFunctionLexem(const std::string& funcName) {
        return Lexem(funcName, FUNCTION, 0, nullptr, 5);
    }
    
    Lexem createBracketLexem(char bracket) {
        LexemType type;
    
        if (bracket == '(' || bracket == '[' || bracket == '{') {
            type = OPEN_BRACKET;
        }
        if (bracket == '|') {
            type = MODULE;
        }
        else {
            type = CLOSE_BRACKET;
        }

        std::string bracketStr(1, bracket); //(символов, символ)
    
        return Lexem(bracketStr, type);
    }
    
    Lexem createVariableLexem(const std::string& varName) {
        return Lexem(varName, VARIABLE);
    }
    
    bool isValidVariableName(const std::string& name) {
        if (name.empty() || name.length() > 5) return false;
        if (std::isdigit(name[0])) return false;
        
        return true;
    }
}