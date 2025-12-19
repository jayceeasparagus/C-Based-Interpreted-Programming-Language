#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    // Keywords
    TOKEN_NUM,
    TOKEN_BOOL,
    TOKEN_STRING,
    TOKEN_MODULE,
    TOKEN_INPUT,
    TOKEN_OUTPUT,
    TOKEN_IF,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_PRINT,

    // Identifier
    TOKEN_IDENTIFIER,

    // Numerical Literal
    TOKEN_NUMBER,

    // Operators
    TOKEN_ADD, // X
    TOKEN_SUBTRACT, // X
    TOKEN_MULTIPLY, // X
    TOKEN_DIVIDE, // X
    TOKEN_LOGICAND, // X
    TOKEN_LOGICOR, // X
    TOKEN_BITAND,
    TOKEN_BITOR,
    TOKEN_XOR, // X
    TOKEN_NOT, // X
    TOKEN_EQUAL, // X
    TOKEN_EQUALITY, // X
    TOKEN_NE, // X
    TOKEN_LT, // X
    TOKEN_GT, // X
    TOKEN_LTE, // X
    TOKEN_GTE, // X

    // Delimiters and symbols
    TOKEN_LPAREN, // X
    TOKEN_RPAREN, // X
    TOKEN_LBRACE, // X
    TOKEN_RBRACE, // X
    TOKEN_COMMA, // X
    TOKEN_SEMICOLON, // X
    TOKEN_EOF, // X

    // Unknown
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    const char *lexeme;
    int value;
    int line;
} Token;

const char *token_type_name(TokenType type);


void print_token(Token t);

typedef struct {
    const char *src;
    int pos;
    int line;
} Lexer;

Token make_token(TokenType type, const char *lexeme, int value, int line);

void skip_whitespace(Lexer *lexer);

Token make_token_number(Lexer *lexer);

Token make_token_identifier_keyword(Lexer *lexer);

Token next_token(Lexer *lexer);

#endif