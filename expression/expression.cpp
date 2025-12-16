#include "expression.h"
#include "../parser/parser.h"
#include "../lib_list/list.h"
#include "../lib_stack/stack.h"

#include <cmath>
#include <iostream>

Expression::Expression(const std::string& str) : original_expression(str) {
    expression = Parser::parse(str);
    construct_polish_record();
}

Expression::~Expression()
{
}

// Построение обратной польской записи
void Expression::construct_polish_record() {
    Stack<Lexem> op_stack(expression.count());
    //polish_record.clear();

    for (List<Lexem>::Iterator it = expression.begin(); it != expression.end(); ++it) {
        Lexem current = expression.head()->_value;
        
        switch (current.type) {
            case NUMBER:
                polish_record.push_back(current);
                break;
            case VARIABLE:
                polish_record.push_back(current);
                break;

            case OPEN_BRACKET:
                op_stack.push(current);
                break;
                
            case CLOSE_BRACKET:
                // понимаем какую скобку будем искать
                char target_open;
                if (current.name == ")") {
                    target_open = '(';
                }
                else if (current.name == "]") {
                    target_open = '[';
                }
                else {
                    target_open = '{';
                }
                
                while (op_stack.top().type != OPEN_BRACKET) {
                    polish_record.push_back(op_stack.top());
                    op_stack.pop();
                }
                
                // Проверяем соответствие скобок
                if (op_stack.top().name[0] != target_open) {
                    throw std::logic_error("Mismatched bracket types");
                }
                
                op_stack.pop(); // Удаляем открывающую скобку
                
                // Если на вершине стека функция, добавляем ее в выход
                if (op_stack.top().type == FUNCTION) {
                    polish_record.push_back(op_stack.top());
                    op_stack.pop();
                }
                break;
                
            case FUNCTION:
                op_stack.push(current);
                break;
                
            case OPERATOR:
            // Если сверху у стека оператор выше по приоритету, то пушим сначала его
                if (op_stack.top().type == OPERATOR) {
                    if (op_stack.top().priority >= current.priority) {
                        polish_record.push_back(op_stack.top());
                        op_stack.pop();
                    }
                }
                polish_record.push_back(current);
                break;
        }
    }
    
    // Выталкиваем оставшиеся операторы из стека
    while (!op_stack.is_empty()) {
        polish_record.push_back(op_stack.top());
        op_stack.pop();
    }
}

// Установка значений переменных
// void Expression::set_variables(const List<double>& values_in) {
//     List<double> values = values_in;
//     // Предполагается, что значения передаются в том же порядке, что и переменные
//     List<std::string> var_list = get_variables();
//     if (var_list.count() != values.count()) {
//         throw std::logic_error("Number of values doesn't match number of variables");
//     }
    
//     List<std::string>::Iterator var_it = var_list.begin();
//     List<double>::Iterator val_it = values.begin();

//     // for (List<Lexem>::Iterator it = expression.begin(); it != expression.end(); ++it) {
//     //     Lexem current = expression.head()->_value;
//     // }
    
//     while (var_it != var_list.end() && val_it != values.end()) {
//         variables[*var_it] = *val_it;
//         ++var_it;
//         ++val_it;
//     }
// }


void Expression::set_variable(const std::string& name, double value) {
    variables[name] = value;
}

// Получение списка переменных
List<std::string> Expression::get_variables() const {
    List<Lexem> expression_copy = expression;
    List<std::string> result;
    
    for (List<Lexem>::Iterator it = expression_copy.begin(); it != expression_copy.end(); ++it) {
        Lexem current = expression_copy.head()->_value;
        if (current.type == VARIABLE) {
            std::string name = current.name;
            bool found = false;
            
            // Проверяем, нет ли уже этой переменной в списке
            for (List<std::string>::Iterator r_it = result.begin(); r_it != result.end(); ++r_it) {
                if (*r_it == name) {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                result.push_back(name);
            }
        }
    }
    
    return result;
}

std::string Expression::get_original() const {
    return original_expression;
}

// Проверка, все ли переменные заданы
bool Expression::all_variables_set() const {
    auto var_list = get_variables();
    
    for (auto it = var_list.begin(); it != var_list.end(); ++it) {
        if (variables.find(*it) == variables.end()) {
            return false;
        }
    }
    
    return true;
}

// Вычисление выражения
double Expression::calculate() {
    if (!all_variables_set()) {
        throw std::logic_error("Not all variables are set");
    }
    
    Stack<double> calc_stack(polish_record.count());
    //Не создается стек
    
    for (List<Lexem>::Iterator it = polish_record.begin(); it != polish_record.end(); ++it) {
        Lexem current = polish_record.head()->_value;
        
        switch (current.type) {
            case NUMBER:
                calc_stack.push(current.value);
                break;
                
            case VARIABLE:
                calc_stack.push(variables[current.name]);
                break;
                
            case OPERATOR: {
                if (calc_stack.size() < 2) {
                    throw std::logic_error("Invalid expression: not enough operands");
                }
                
                // Извлекаются два элемента, первый - второй, второй - первый
                double b = calc_stack.top();
                calc_stack.pop();
                double a = calc_stack.top();
                calc_stack.pop();
                
                double result = 0;
                
                if (current.name == "+") result = a + b;
                else if (current.name == "-") result = a - b;
                else if (current.name == "*") result = a * b;
                else if (current.name == "/") {
                    if (b == 0) throw std::logic_error("Division by zero");
                    result = a / b;
                }
                else if (current.name == "^") result = pow(a, b);
                
                calc_stack.push(result);
                break;
            }
                
            case FUNCTION: {
                if (calc_stack.is_empty()) {
                    throw std::logic_error("Invalid expression: no argument for function");
                }
                
                double arg = calc_stack.top();
                calc_stack.pop();
                
                double result = 0;
                // Сначала стандартную библиотеку - в ней аргумент радианы
                if (current.name == "sin") result = sin(arg);
                else if (current.name == "cos") result = cos(arg);
                else if (current.name == "tg") result = tan(arg);
                //! @todo переделать в свои функции вычисления через ряды
                
                calc_stack.push(result);
                break;
            }
        }
    }
    
    if (calc_stack.size() != 1) {
        throw std::logic_error("Invalid expression");
    }
    
    return calc_stack.top();
}


// double Expression::computeSin(double degrees) const {
//     // Преобразуем градусы в радианы
//     double radians = degrees * 3.14 / 180.0;
    
//     // Приводим угол к диапазону [-π, π] радиан
//     const double pi = 3.14;
//     while (radians > pi) radians -= 2 * pi;
//     while (radians < -pi) radians += 2 * pi;
    
//     double result = 0.0;
//     double term = radians;
//     int n = 1;
    
//     //sin = x - x^3/3! + x^5/5! - x^7/7! + ...
//     for (int i = 0; i < 10; i++) {
//         result += term;
//         n += 2;
//         term = -term * radians^2 / (n * (n - 1));
//     }
    
//     return result;
// }

// double Expression::computeCos(double degrees) const {
//     // Преобразуем градусы в радианы
//     double radians = degrees * 3.14 / 180.0;
    
//     // Приводим угол к диапазону [-π, π] радиан
//     const double pi = 3.14;
//     while (radians > pi) radians -= 2 * pi;
//     while (radians < -pi) radians += 2 * pi;
    
//     double result = 0.0;
//     double term = 1.0;
//     int n = 0;
    
//     // cos = 1 - x^2/2! + x^4/4! - x^6/6! + ...
//     for (int i = 0; i < 10; i++) {
//         result += term;
//         n += 2;
//         term = -term * radians^2 / (n * (n - 1));
//     }
    
//     return result;
// }

// double Expression::computeTg(double degrees) const {
//     double sin_val = computeSin(degrees);
//     double cos_val = computeCos(degrees);
    
//     // cos -> 0
//     if (cos_val < 1e-10 && cos_val > -1e-10) {
//         throw std::logic_error("Tangens undefined for angle: " + std::to_string(degrees) + " degrees");
//     }
    
//     return sin_val / cos_val;
// }
