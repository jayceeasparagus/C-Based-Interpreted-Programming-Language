#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY,
    AST_UNARY,
    AST_PRINT,
    AST_STATEMENTS,
    AST_ASSIGN,
    AST_DECLARATION,
    AST_BOOLEAN,
    AST_COMPARISON,
    AST_IF_ELSE
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

        struct {
            const char *name;
            struct ASTNode *value;
        } assign;

        struct {
            const char *name;
            TokenType type;
            struct ASTNode *value;
        } declaration;

        struct {
            TokenType operand;
            struct ASTNode *left;
            struct ASTNode *right;
        } comparison;

        struct {
            struct ASTNode *condition;
            struct ASTNode *then_statements;
            struct ASTNode *else_statements;
        } if_else;
    };
} ASTNode;

ASTNode *ast_number(double value);

ASTNode *ast_boolean(double boolean);

ASTNode *ast_identifier(const char *name);

ASTNode *ast_binary(TokenType operand, ASTNode *left, ASTNode *right);

ASTNode *ast_unary(TokenType operand, ASTNode *expression);

ASTNode *ast_print(ASTNode *expression);

ASTNode *ast_statements(ASTNode **statements, int count);

ASTNode *ast_assign(const char *name, ASTNode *value);

ASTNode *ast_declaration(const char *name, TokenType type, ASTNode *value);

ASTNode *ast_comparison(TokenType operand, ASTNode *left, ASTNode *right);

ASTNode *ast_if_else(ASTNode *condition, ASTNode *then_statements, ASTNode *else_statements);

void ast_print_tree(ASTNode *node, int indent);

#endif