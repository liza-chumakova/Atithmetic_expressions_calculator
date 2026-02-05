#include "../parser/parser.h"
#include "../calculator/calculator.h"

const char *const TypesMap[] = {
  "ERROR",
  "OPEN_BRACKET",
  "CLOSE_BRACKET",
  "MODULE",
  "OPERATOR",
  "VARIABLE",
  "FUNCTION",
  "NUMBER",
};

int main() {

    const List<Lexem> &res1 = Parser::parse("(17+xyz)*123*sin(b)*(-23)");

    List<Lexem>::ConstIterator it1;
    for (it1 = res1.cbegin(); it1 != res1.cend(); ++it1) {
      const Lexem &lex = *it1;
      printf("Token type: [%s], name: [%s], value: [%g]\n", TypesMap[lex.type], lex.name.c_str(), lex.value);
    }

    printf("\n");

    const List<Lexem> &res = Parser::parse("(17+42)*123*sin(13)*(-23)");

    List<Lexem>::ConstIterator it;
    for (it = res.cbegin(); it != res.cend(); ++it) {
      const Lexem &lex = *it;
      printf("Token type: [%s], name: [%s], value: [%g]\n", TypesMap[lex.type], lex.name.c_str(), lex.value);
    }

    printf("Expression2 \n\n");



    //Expression ex("(17+xyz)*123*sin(3)*(-23)");
    Expression ex("(17+42)*123*sin(13)*(-23)");

    //const List<std::string> &vars = ex.get_variables();
    List<std::string>::ConstIterator it2;
    printf("%s", "abracadabra11111111\n");

    // for (it2 = vars.cbegin(); it2 != vars.cend(); ++it2) {
    //   printf("%s", "abracadabra22222222\n");
    //   const std::string &val = *it2;
    //   printf("Val: [%s]\n", val.c_str());
    // }


    //Expression res2("(17+xyz)*123*sin(3)*(-23)");
    // List<std::string>::ConstIterator it2;
    // int count = 1;
    // printf("%s", "abracadabra11111111");
    // for (it2 = res2.get_variables().cbegin(); it2 != res2.get_variables().cend(); ++it2) {
    //     printf("%s", "abracadabra2222222");
    //     const std::string &str = *it2;
    //     printf("Variable [%d]: name: [%s]\n", count, str);
    //     ++count;
    // }

    // List<double> vars1 = ({1});
    // res2.set_variables(vars1);
    // res2.calculate();

    Calculator calculator;
    calculator.run();

    return 0;
}