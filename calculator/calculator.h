#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "../lib_list/list.h"
#include "../expression/expression.h"

class Calculator {
private:
    List<Expression> expressions;

    void print_menu() const;
    void create_expression();
    void delete_expression();
    void set_variables();
    void calculate_expression();
    void show_expressions() const;
    
public:
    void run();
};

#endif //CALCULATOR_H