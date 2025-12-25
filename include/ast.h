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
    AST_IF_ELSE, 
    AST_WHILE,
    AST_MODULE,
    AST_CALL
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

        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_loop;

        struct {
            const char *name;
            char **inputs;
            int input_count;
            char **outputs;
            int output_count;
            struct ASTNode *body;
        } module;

        struct {
            const char *name;
            struct ASTNode **args;
            int arg_count;
        } call;
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

ASTNode *ast_while_loop(ASTNode *condition, ASTNode *body);

ASTNode *ast_module(const char *name, char **inputs, int input_count, char **outputs, int output_count, ASTNode *body);

ASTNode *ast_call(const char *name, ASTNode **args, int arg_count);

void ast_print_tree(ASTNode *node, int indent);

#endif