#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"

int main() {
    const char *source =
    "num a = 5;\n"
    "a = a + 2;\n"
    "print(a);\n"
    "bool b = true;\n"
    "bool c = false;\n"
    "print(!b || c);\n";

    Lexer lexer = { source, 0, 1 };

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    //ast_print_tree(program, 0);

    eval(program);

    return 0;
}

// ADD UNARY