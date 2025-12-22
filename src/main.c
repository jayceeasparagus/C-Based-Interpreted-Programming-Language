#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"

int main() {
    const char *source =
        "print(1 + 2 * 3);\n"
        "print((1 + 2) * 3);\n"
        "print(4 & 3 | 1);\n";

    Lexer lexer = { source, 0, 1 };
    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    eval(program);

    return 0;
}

