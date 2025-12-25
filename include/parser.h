#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer *lexer;
    Token current;
    Token next;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);

TokenType peek_token(Parser *parser);

ASTNode *parse_program(Parser *parser);

ASTNode *parse_statements(Parser *parser);

ASTNode *parse_if_else(Parser *parser);

ASTNode *parse_while_loop(Parser *parser);

void parse_params(Parser *parser, char ***inputs, int *input_count, char ***outputs, int *output_count);

ASTNode *parse_module(Parser *parser);

ASTNode *parse_call(Parser *parser);

ASTNode *parse_statement(Parser *parser);

ASTNode *parse_declaration(Parser *parser);

ASTNode *parse_assignment(Parser *parser);

ASTNode *parse_print(Parser *parser);

int comparison_operator(TokenType type);

ASTNode *parse_comparison(Parser *parser);

int expression_operator(TokenType type);

ASTNode *parse_expression(Parser *parser);

int term_operator(TokenType type);

ASTNode *parse_term(Parser *parser);

ASTNode *parse_unary(Parser *parser);

ASTNode *parse_factor(Parser *parser);