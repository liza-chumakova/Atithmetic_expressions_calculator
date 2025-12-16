#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "../lib_list/list.h"
#include "../expression/expression.h"

namespace Parser {
    // Разбор строки в список лексем
    List<Lexem> parse(const std::string& expression);
};

#endif