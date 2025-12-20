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
    TOKEN_ADD,
    TOKEN_SUBTRACT,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LOGICAND,
    TOKEN_LOGICOR,
    TOKEN_BITAND,
    TOKEN_BITOR,
    TOKEN_XOR,
    TOKEN_NOT,
    TOKEN_EQUAL,
    TOKEN_EQUALITY,
    TOKEN_NE,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LTE,
    TOKEN_GTE,

    // Delimiters and symbols
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_EOF,

    // Unknown
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    const char *lexeme;
    double value;
    int line;
} Token;

const char *token_type_name(TokenType type);


void print_token(Token t);

typedef struct {
    const char *src;
    int pos;
    int line;
} Lexer;

Token make_token(TokenType type, const char *lexeme, double value, int line);

void skip_whitespace(Lexer *lexer);

Token make_token_number(Lexer *lexer);

Token make_token_identifier_keyword(Lexer *lexer);

Token next_token(Lexer *lexer);

#endif