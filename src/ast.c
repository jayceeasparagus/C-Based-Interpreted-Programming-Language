#include "ast.h"

ASTNode *ast_number(double value) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_NUMBER;
    astnode->number = value;
    return astnode;
}

ASTNode *ast_identifier(const char *name) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_IDENTIFIER;
    astnode->identifier = name;
    return astnode;
}

ASTNode *ast_binary(TokenType operand, ASTNode *left, ASTNode *right) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_BINARY;
    astnode->binary.operand = operand;
    astnode->binary.left = left;
    astnode->binary.right = right;
    return astnode;
}

ASTNode *ast_unary(TokenType operand, ASTNode *expression) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_UNARY;
    astnode->unary.operand = operand;
    astnode->unary.expression = expression;
    return astnode;
}

ASTNode *ast_print(ASTNode *expression) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_PRINT;
    astnode->print.expression = expression;
    return astnode;
}

ASTNode *ast_statements(ASTNode **statements, int count) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_STATEMENTS;
    astnode->statements.statements = statements;
    astnode->statements.count = count;
    return astnode;
}

void ast_print_tree(ASTNode *node, int indent) {
    if (!node) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    switch (node->type) {
        case AST_NUMBER:
            printf("%.2f\n", node->number);
            break;
        case AST_IDENTIFIER:
            printf("%s\n", node->identifier);
            break;
        case AST_BINARY:
            printf("%s\n", token_type_name(node->binary.operand));
            ast_print_tree(node->binary.left, indent + 1);
            ast_print_tree(node->binary.right, indent + 1);
            break;
        case AST_UNARY:
            printf("%s\n", token_type_name(node->unary.operand));
            ast_print_tree(node->unary.expression, indent + 1);
            break;
        case AST_PRINT:
            printf("PRINT\n");
            ast_print_tree(node->print.expression, indent + 1);
            break;
        case AST_STATEMENTS:
            printf("STATEMENTS\n");
            for (int i = 0; i < node->statements.count; ++i) {
                ast_print_tree(node->statements.statements[i], indent + 1);
            }
            break;
    }
}