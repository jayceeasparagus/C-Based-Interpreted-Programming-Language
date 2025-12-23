#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer *lexer;
    Token current;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);

ASTNode *parse_program(Parser *parser);

ASTNode *parse_statement(Parser *parser);

ASTNode *parse_declaration(Parser *parser);

ASTNode *parse_assignment(Parser *parser);

ASTNode *parse_print(Parser *parser);

int expression_operator(TokenType type);

ASTNode *parse_expression(Parser *parser);

int term_operator(TokenType type);

ASTNode *parse_term(Parser *parser);

ASTNode *parse_unary(Parser *parser);

ASTNode *parse_factor(Parser *parser);