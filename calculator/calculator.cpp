#include "calculator.h"
#include <iostream>
#include <iomanip>
#include <limits>

void Calculator::print_menu() const {
    std::cout << "\n============= Arithmetic Expressions Calculator =============\n";
    std::cout << "1. Create new expression\n";
    std::cout << "2. Delete expression\n";
    std::cout << "3. Set variables for expression\n";
    std::cout << "4. Calculate expression\n";
    std::cout << "5. Show all expressions\n";
    std::cout << "6. Exit\n";
    std::cout << "Choice: ";
}

void Calculator::create_expression() {
    std::cout << "Enter expression: ";
    std::string expr_str;
    std::getline(std::cin, expr_str);
    
    try {
        Expression expr(expr_str);
        expressions.push_back(expr);
        std::cout << "Expression added successfully!\n";
        std::cout << "Variables in expression: ";
        
        auto vars = expr.get_variables();
        if (vars.is_empty()) {
            std::cout << "none";
        } else {
            for (auto it = vars.begin(); it != vars.end(); ++it) {
                std::cout << *it << " ";
            }
        }
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        
        // Показываем место ошибки
        size_t pos = 0;
        if (std::string(e.what()).find("at position") != std::string::npos) {
            // Извлекаем позицию из сообщения об ошибке
        }
    }
}

void Calculator::delete_expression() {
    show_expressions();
    
    if (expressions.is_empty()) {
        std::cout << "No expressions to delete.\n";
        return;
    }
    
    std::cout << "Enter expression number to delete (1-" << expressions.count() - 1 << "): ";
    size_t index;
    std::cin >> index;
    
    if (index < 1 || index > expressions.count()) {
        std::cout << "Invalid index.\n";
        return;
    }
    
    Node<Expression> toDelete = expressions.head()->_value;
    List<Expression>::Iterator it = expressions.begin();
    for (size_t i = 1; i < index; ++i) {
        toDelete = toDelete._next->_value;
        ++it;
    }
    
    expressions.pop(&toDelete);
    std::cout << "Expression deleted.\n";
}

void Calculator::set_variables() {
    show_expressions();
    
    if (expressions.is_empty()) {
        std::cout << "No expressions available.\n";
        return;
    }
    
    std::cout << "Enter expression number (1-" << expressions.count() << "): ";
    size_t index;
    std::cin >> index;
    
    if (index < 1 || index > expressions.count()) {
        std::cout << "Invalid index.\n";
        return;
    }
    
    // Получаем выражение по индексу
    List<Expression>::Iterator it = expressions.begin();
    for (size_t i = 1; i < index; ++i) {
        ++it;
    }
    
    Expression& expr = *it;
    List<std::string> vars = expr.get_variables();
    
    if (vars.is_empty()) {
        std::cout << "This expression has no variables.\n";
        return;
    }
    
    std::cout << "Variables in expression: ";
    for (List<std::string>::Iterator var_it = vars.begin(); var_it != vars.end(); ++var_it) {
        std::cout << *var_it << " ";
    }
    std::cout << "\n";
    
    for (List<std::string>::Iterator var_it = vars.begin(); var_it != vars.end(); ++var_it) {
        std::cout << "Enter value for " << *var_it << ": ";
        double value;
        std::cin >> value;
        
        expr.set_variable(*var_it, value);
    }
    
    std::cout << "Variables set successfully.\n";
}

void Calculator::calculate_expression() {
    show_expressions();
    
    if (expressions.is_empty()) {
        std::cout << "No expressions available.\n";
        return;
    }
    
    std::cout << "Enter expression number (1-" << expressions.count() << "): ";
    size_t index;
    std::cin >> index;
    
    if (index < 1 || index > expressions.count()) {
        std::cout << "Invalid index.\n";
        return;
    }
    
    List<Expression>::Iterator it = expressions.begin();
    for (size_t i = 1; i < index; ++i) {
        ++it;
    }
    Expression exp = *it;
    
    double result = exp.calculate();
    std::cout << "Result: " << result << "\n";
    
}

void Calculator::show_expressions() const {
    if (expressions.is_empty()) {
        std::cout << "No expressions available.\n";
        return;
    }
    
    List<Expression> expressions_copy = expressions;
    Node<Expression> cur_expression = expressions_copy.head()->_value;
    std::cout << "\n=== Expressions List ===\n";
    size_t counter = 1;
    for (List<Expression>::Iterator it = expressions_copy.begin(); it != expressions_copy.end(); ++it) {
        std::cout << counter++ << ". " << cur_expression._value.get_original() << "\n";
        cur_expression = cur_expression._next->_value;
    }
}

void Calculator::run() {
    int choice = 0;
    
    while (choice != 6) {
        print_menu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                create_expression();
                break;
            case 2:
                delete_expression();
                break;
            case 3:
                set_variables();
                break;
            case 4:
                calculate_expression();
                break;
            case 5:
                show_expressions();
                break;
            case 6:
                std::cout << "The End!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}