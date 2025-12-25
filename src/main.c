#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"
#include "env.h"

int main() {
    const char *source =
    "module add(input a, input b, output c) {\n"
    "c = a + b;\n"
    "}\n"
    "num x = 2;\n"
    "num y = 3;\n"
    "num z = 0;\n"
    "add(x, y, z);\n"
    "print(z);\n"
    "bool h = true;\n"
    "print(!h || true);\n";

    Lexer lexer = { source, 0, 1 };

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    env_init();
    eval(program);

    return 0;
}