#pragma once

#include "../lib_list/list.h"
#include "../lib_stack/stack.h"

#include <string>
#include <functional>
#include <unordered_map>

enum LexemType {
    ERROR,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    MODULE,
    OPERATOR,
    VARIABLE,
    FUNCTION,
    NUMBER
};

typedef double (*func_type)(double);

struct Lexem {
    std::string name;
    double value;
    int priority;
    LexemType type;
    func_type function;
    
    // Конструкторы
    Lexem() : name(""), value(0), priority(0), type(ERROR), function(nullptr) {}
    
    Lexem(const std::string &n, LexemType t, double v = 0, func_type f = nullptr, int p = 0) 
        : name(n), value(v), priority(p), type(t), function(f) {}
    //Lexem(Name, LexemType, value, priority, *function);
};

class Expression {
private:
    List<Lexem> expression;
    List<Lexem> polish_record;
    std::unordered_map<std::string, double> variables;
    std::string original_expression;
    
public:
    Expression(const std::string& str);

    ~Expression();
    
    // Построение обратной польской записи
    void construct_polish_record();
    
    // Установка значений переменных
    //void set_variables(const List<double>& values);
    
    // Установка значения конкретной переменной
    void set_variable(const std::string& name, double value);
    
    // Вычисление выражения
    double calculate();
    
    // Получение списка переменных
    List<std::string> get_variables() const;

    // Получение строки выражения
    std::string get_original() const;
    
    // Проверка, все ли переменные заданы
    bool all_variables_set() const;
};

// Математические функции (градусы в радианы)
// namespace MathFunctions {
//     double degToRad(double degrees);
//     double sin_deg(double degrees);
//     double cos_deg(double degrees);
//     double tg_deg(double degrees);
//     double abs_val(double value);
// }
