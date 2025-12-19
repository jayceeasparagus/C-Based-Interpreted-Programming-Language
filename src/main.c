#include "lexer.h"
#include <stdio.h>

int main() {
    const char *source =
        "num a = 0b1010;\n"
        "num b = 12;\n"
        "if (a ^ b > 3) {\n"
        "    print(a & b);\n"
        "}\n";

    Lexer lexer;
    lexer.src = source;
    lexer.pos = 0;
    lexer.line = 1;

    Token t;
    do {
        t = next_token(&lexer);
        print_token(t);
    } while (t.type != TOKEN_EOF);

    return 0;
}
