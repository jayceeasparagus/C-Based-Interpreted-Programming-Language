#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"

int main() {
    const char *source =
    "num i = 0;\n"

    "while (i < 3) {\n"
    "print(i);\n"
    "i = i + 1;\n"
    "}\n";


    Lexer lexer = { source, 0, 1 };

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    ast_print_tree(program, 0);

    eval(program);

    return 0;
}