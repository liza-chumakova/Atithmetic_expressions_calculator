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
    //Calculator calculator;
    //calculator.run();

    const List<Lexem> &res = Parser::parse("(17+42)*123*sin(13)*(-23)");

    List<Lexem>::ConstIterator it;
    for (it = res.cbegin(); it != res.cend(); ++it) {
      const Lexem &lex = *it;
      printf("Token type: [%s], name: [%s], value: [%g]\n", TypesMap[lex.type], lex.name.c_str(), lex.value);
    }

    printf("\n");

    const List<Lexem> &res1 = Parser::parse("(17+xyz)*123*sin(b)*(-23)");

    List<Lexem>::ConstIterator it1;
    for (it1 = res1.cbegin(); it1 != res1.cend(); ++it1) {
      const Lexem &lex = *it1;
      printf("Token type: [%s], name: [%s], value: [%g]\n", TypesMap[lex.type], lex.name.c_str(), lex.value);
    }

    // Expression res2("(17+xyz)*123*sin(3)*(-23)");

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

    return 0;
}