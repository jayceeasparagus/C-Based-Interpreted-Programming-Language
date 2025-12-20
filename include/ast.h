#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY,
    AST_UNARY,
    AST_PRINT,
    AST_STATEMENTS
} ASTType;

typedef struct ASTNode {
    ASTType type;

    union {
        double number;
        const char *identifier;
        struct {
            TokenType operand;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;

        struct {
            TokenType operand;
            struct ASTNode *expression;
        } unary;

        struct {
            struct ASTNode *expression;
        } print;

        struct {
            struct ASTNode **statements;
            int count;
        } statements;
    };
} ASTNode;

ASTNode *ast_number(double value);

ASTNode *ast_identifier(const char *name);

ASTNode *ast_binary(TokenType operand, ASTNode *left, ASTNode *right);

ASTNode *ast_unary(TokenType operand, ASTNode *expression);

ASTNode *ast_print(ASTNode *expression);

ASTNode *ast_statements(ASTNode **statements, int count);

void ast_print_tree(ASTNode *node, int indent);

#endif