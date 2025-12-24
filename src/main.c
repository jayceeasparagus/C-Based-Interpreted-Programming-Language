#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"

int main() {
    const char *source =
    "if (5 < 3) {\n"
    "print(1);\n"
    "}\n"
    "elif (6 == 2) {\n"
    "print(2);\n"
    "}\n"
    "else {\n"
    "print(3);\n"
    "}\n";

    Lexer lexer = { source, 0, 1 };

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    ast_print_tree(program, 0);

    eval(program);

    return 0;
}