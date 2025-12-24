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

ASTNode *parse_statements(Parser *parser) {
    expect(parser, TOKEN_LBRACE);

    ASTNode **statements = NULL;
    int count = 0;

    while (parser->current.type != TOKEN_RBRACE) {
        statements = realloc(statements, sizeof(*statements) * (count + 1));
        statements[count++] = parse_statement(parser);
    }

    expect(parser, TOKEN_RBRACE);
    return ast_statements(statements, count);
}

ASTNode *parse_if_else(Parser *parser) {
    expect(parser, TOKEN_IF);
    expect(parser, TOKEN_LPAREN);

    ASTNode *condition = parse_comparison(parser);

    expect(parser, TOKEN_RPAREN);

    ASTNode *then_statements = parse_statements(parser);

    ASTNode *root = ast_if_else(condition, then_statements, NULL);
    ASTNode *current = root;

    while (parser->current.type == TOKEN_ELIF) {
        advance(parser);
        expect(parser, TOKEN_LPAREN);

        ASTNode *elif_condition = parse_comparison(parser);

        expect(parser, TOKEN_RPAREN);
        ASTNode *elif_statements = parse_statements(parser);

        current->if_else.else_statements = ast_if_else(elif_condition, elif_statements, NULL);
        current = current->if_else.else_statements;
    }

    if (parser->current.type == TOKEN_ELSE) {
        advance(parser);
        current->if_else.else_statements = parse_statements(parser);
    }

    return root;
}

ASTNode *parse_while_loop(Parser *parser) {
    expect(parser, TOKEN_WHILE);
    expect(parser, TOKEN_LPAREN);

    ASTNode *condition = parse_comparison(parser);

    expect(parser, TOKEN_RPAREN);
    ASTNode *body = parse_statements(parser);

    return ast_while_loop(condition, body);
}

ASTNode *parse_statement(Parser *parser) {
    switch (parser->current.type) {
        case TOKEN_PRINT:
            return parse_print(parser);
        case TOKEN_NUM:
            return parse_declaration(parser);
        case TOKEN_BOOL:
            return parse_declaration(parser);
        case TOKEN_IDENTIFIER:
            return parse_assignment(parser);
        case TOKEN_IF:
            return parse_if_else(parser);
        case TOKEN_WHILE:
            return parse_while_loop(parser);
        default:
            printf("ERROR: Incorrect statement token at: %d\n", parser->current.line);
            exit(1);
    }
}

ASTNode *parse_declaration(Parser *parser) {
    TokenType type = parser->current.type;
    advance(parser);

    const char *name = parser->current.lexeme;
    expect(parser, TOKEN_IDENTIFIER);

    expect(parser, TOKEN_ASSIGN);
    ASTNode *value = parse_comparison(parser);

    expect(parser, TOKEN_SEMICOLON);
    return ast_declaration(name, type, value);
}

ASTNode *parse_assignment(Parser *parser) {
    const char *name = parser->current.lexeme;
    expect(parser, TOKEN_IDENTIFIER);

    expect(parser, TOKEN_ASSIGN);
    ASTNode *value = parse_comparison(parser);

    expect(parser, TOKEN_SEMICOLON);
    return ast_assign(name, value);
}

ASTNode *parse_print(Parser *parser) {
    expect(parser, TOKEN_PRINT);
    expect(parser, TOKEN_LPAREN);

    ASTNode *expression = parse_comparison(parser);

    expect(parser, TOKEN_RPAREN);
    expect(parser, TOKEN_SEMICOLON);

    return ast_print(expression);
}

int comparison_operator(TokenType type) {
    return (type == TOKEN_EQUALITY || type == TOKEN_NE ||
    type == TOKEN_LT || type == TOKEN_GT || 
    type == TOKEN_LTE || type == TOKEN_GTE);
}

ASTNode *parse_comparison(Parser *parser) {
    ASTNode *left = parse_expression(parser);

    if (comparison_operator(parser->current.type)) {
        TokenType operand = parser->current.type;
        advance(parser);
        ASTNode *right = parse_expression(parser);
        return ast_comparison(operand, left, right);
    }

    return left;
}

int expression_operator(TokenType type) {
    return (type == TOKEN_ADD || type == TOKEN_SUBTRACT || 
    type == TOKEN_BITOR || type == TOKEN_XOR ||
    type == TOKEN_LOGICOR);
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
        type == TOKEN_BITAND || type == TOKEN_LOGICAND);
}

ASTNode *parse_term(Parser *parser) {
    ASTNode *left = parse_unary(parser);

    while (term_operator(parser->current.type)) {
        TokenType operand = parser->current.type;
        advance(parser);
        ASTNode *right = parse_unary(parser);
        left = ast_binary(operand, left, right);
    }

    return left;
}

ASTNode *parse_unary(Parser *parser) {
    if (parser->current.type == TOKEN_NOT || parser->current.type == TOKEN_SUBTRACT) {
        TokenType operand = parser->current.type;
        advance(parser);
        ASTNode *right = parse_unary(parser);
        return ast_unary(operand, right);
    }

    return parse_factor(parser);
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
        ASTNode *expression = parse_comparison(parser);
        expect(parser, TOKEN_RPAREN);
        return expression;
    }
    if (parser->current.type == TOKEN_TRUE) {
        advance(parser);
        return ast_boolean(1);
    }
    if (parser->current.type == TOKEN_FALSE) {
        advance(parser);
        return ast_boolean(0);
    }
    if (parser->current.type == TOKEN_IDENTIFIER) {
        const char *name = parser->current.lexeme;
        advance(parser);
        return ast_identifier(name);
    }
    printf("ERROR: Incorrect factor token at: %d\n", parser->current.line);
    exit(1);
}