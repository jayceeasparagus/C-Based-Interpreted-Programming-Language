#include "parser.h"

void parser_init(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
    parser->current = next_token(lexer);
}

static void advance(Parser *parser) {
    parser->current = next_token(parser->lexer);
}

static void expect(Parser *parser, TokenType type) {
    if (parser->current.type != type) {
        printf("Error: Incorrect token type expected at: %d\n", parser->current.line);
        exit(1);
    }
    advance(parser);
}

ASTNode *parse_program(Parser *parser) {
    ASTNode **statements = NULL;
    int count = 0;

    while (parser->current.type != TOKEN_EOF) {
        statements = realloc(statements, sizeof(*statements) * (count + 1));
        statements[count++] = parse_statement(parser);
    }

    return ast_statements(statements, count);
}

ASTNode *parse_statement(Parser *parser) {
    switch (parser->current.type) {
        case TOKEN_PRINT:
            return parse_print(parser);
        default:
            printf("ERROR: Incorrect statement token at: %d\n", parser->current.line);
            exit(1);
    }
}

ASTNode *parse_print(Parser *parser) {
    expect(parser, TOKEN_PRINT);
    expect(parser, TOKEN_LPAREN);

    ASTNode *expression = parse_expression(parser);

    expect(parser, TOKEN_RPAREN);
    expect(parser, TOKEN_SEMICOLON);

    return ast_print(expression);
}

int expression_operator(TokenType type) {
    return (type == TOKEN_ADD || type == TOKEN_SUBTRACT || 
    type == TOKEN_BITOR || type == TOKEN_XOR);
}

ASTNode *parse_expression(Parser *parser) {
    ASTNode *left = parse_term(parser);

    while (expression_operator(parser->current.type)) {
        TokenType operand = parser->current.type;
        advance(parser);
        ASTNode *right = parse_term(parser);
        left = ast_binary(operand, left, right);
    }

    return left;
}

int term_operator(TokenType type) {
    return (type == TOKEN_MULTIPLY || type == TOKEN_DIVIDE || 
        type == TOKEN_BITAND);
}

ASTNode *parse_term(Parser *parser) {
    ASTNode *left = parse_factor(parser);

    while (term_operator(parser->current.type)) {
        TokenType operand = parser->current.type;
        advance(parser);
        ASTNode *right = parse_factor(parser);
        left = ast_binary(operand, left, right);
    }

    return left;
}

ASTNode *parse_factor(Parser *parser) {
    // high precedence
    if (parser->current.type == TOKEN_NUMBER) {
        double value = parser->current.value;
        advance(parser);
        return ast_number(value);
    }
    if (parser->current.type == TOKEN_LPAREN) {
        advance(parser);
        ASTNode *expression = parse_expression(parser);
        expect(parser, TOKEN_RPAREN);
        return expression;
    }
    printf("ERROR: Incorrect factor token at: %d\n", parser->current.line);
    exit(1);
}