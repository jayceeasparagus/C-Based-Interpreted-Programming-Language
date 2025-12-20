#include <stdio.h>
#include "ast.h"

int main() {
    // Build AST for: 1 + 2 * 3

    ASTNode *one   = ast_number(1);
    ASTNode *two   = ast_number(2);
    ASTNode *three = ast_number(3);

    ASTNode *mul = ast_binary(TOKEN_MULTIPLY, two, three);
    ASTNode *add = ast_binary(TOKEN_ADD, one, mul);

    ASTNode *print = ast_print(add);

    ast_print_tree(print, 0);

    return 0;
}
