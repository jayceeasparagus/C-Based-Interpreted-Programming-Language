#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

int main() {
    const char *source =
        "print(1 + 2 * 3);\n"
        "print((1 + 2) * 3);\n";

    Lexer lexer = { source, 0, 1 };
    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    ast_print_tree(program, 0);

    return 0;
}

