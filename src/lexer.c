#include "lexer.h"

const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_NUM:
            return "NUM";
        case TOKEN_BOOL:
            return "BOOL";
        case TOKEN_STRING:
            return "STRING";
        case TOKEN_MODULE:
            return "MODULE";
        case TOKEN_INPUT:
            return "INPUT";
        case TOKEN_OUTPUT:
            return "OUTPUT";
        case TOKEN_IF:
            return "IF";
        case TOKEN_ELIF:
            return "ELIF";
        case TOKEN_ELSE:
            return "ELSE";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_PRINT:
            return "PRINT";

        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";
        case TOKEN_NUMBER:
            return "NUMBER";
        case TOKEN_TRUE:
            return "TRUE";
        case TOKEN_FALSE:
            return "FALSE";

        case TOKEN_ADD:
            return "ADD";
        case TOKEN_SUBTRACT:
            return "SUBTRACT";
        case TOKEN_MULTIPLY:
            return "MULTIPLY";
        case TOKEN_DIVIDE:
            return "DIVIDE";
        case TOKEN_LOGICAND:
            return "LOGICAND";
        case TOKEN_LOGICOR:
            return "LOGICOR";
        case TOKEN_BITAND:
            return "BITAND";
        case TOKEN_BITOR:
            return "BITOR";
        case TOKEN_XOR:
            return "XOR";
        case TOKEN_NOT:
            return "NOT";

        case TOKEN_ASSIGN:
            return "ASSIGN";
        case TOKEN_EQUALITY:
            return "EQUALITY";
        case TOKEN_NE:
            return "NE";
        case TOKEN_LT:
            return "LT";
        case TOKEN_GT:
            return "GT";
        case TOKEN_LTE:
            return "LTE";
        case TOKEN_GTE:
            return "GTE";

        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";
        case TOKEN_LBRACE:
            return "LBRACE";
        case TOKEN_RBRACE:
            return "RBRACE";
        case TOKEN_COMMA:
            return "COMMA";
        case TOKEN_SEMICOLON:
            return "SEMICOLON";

        case TOKEN_EOF:
            return "EOF";
        default:
            return "UNKNOWN";
    }
}

void print_token(Token t) {
    printf("TOKEN %-12s", token_type_name(t.type));
    if (t.type == TOKEN_IDENTIFIER) {
        printf(" name=%s", t.lexeme);
    }
    if (t.type == TOKEN_NUMBER) {
        printf(" value=%.2f", t.value);
    }
    printf("\n");
}

Token make_token(TokenType type, const char *lexeme, double value, int line) {
    Token token;
    token.type = type;
    token.lexeme = lexeme;
    token.value = value;
    token.line = line;
    return token;
}

void skip_whitespace(Lexer *lexer) {
    // loop until no whitespace or eof
    while (lexer->src[lexer->pos] != '\0') {
        if (lexer->src[lexer->pos] == '\n') {
            lexer->pos++;
            lexer->line++;
        }
        else if (lexer->src[lexer->pos] == ' ' || lexer->src[lexer->pos] == '\t' || lexer->src[lexer->pos] == '\r') {
            lexer->pos++;
        }
        else {
            break;
        }
    }
}

Token make_token_number(Lexer *lexer) {
    int value = 0;

    // binary
    if (lexer->src[lexer->pos] == '0' && lexer->src[lexer->pos + 1] == 'b') {
        lexer->pos += 2;
        
        while (lexer->src[lexer->pos] == '0' || lexer->src[lexer->pos] == '1') {
            value = value * 2 + (lexer->src[lexer->pos] - '0');
            lexer->pos++;
        }
    }
    // decimal
    else {
        while (isdigit(lexer->src[lexer->pos])) {
            value = value * 10 + (lexer->src[lexer->pos] - '0');
            lexer->pos++;
        }
    }

    return make_token(TOKEN_NUMBER, NULL, value, lexer->line);
}

Token make_token_identifier_keyword(Lexer *lexer) {
    int start = lexer->pos;

    while (isalnum(lexer->src[lexer->pos]) || lexer->src[lexer->pos] == '_') {
        lexer->pos++;
    }

    int length = lexer->pos - start;

    char *text = malloc(length + 1);
    memcpy(text, lexer->src + start, length);
    text[length] = '\0';

    if (strcmp(text, "num") == 0) {
        Token token = make_token(TOKEN_NUM, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "bool") == 0) {
        Token token = make_token(TOKEN_BOOL, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "string") == 0) {
        Token token = make_token(TOKEN_STRING, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "module") == 0) {
        Token token = make_token(TOKEN_MODULE, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "input") == 0) {
        Token token = make_token(TOKEN_INPUT, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "output") == 0) {
        Token token = make_token(TOKEN_OUTPUT, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "if") == 0) {
        Token token = make_token(TOKEN_IF, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "elif") == 0) {
        Token token = make_token(TOKEN_ELIF, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "else") == 0) {
        Token token = make_token(TOKEN_ELSE, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "while") == 0) {
        Token token = make_token(TOKEN_WHILE, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "print") == 0) {
        Token token = make_token(TOKEN_PRINT, text, 0, lexer->line);
        return token;
    }
    else if (strcmp(text, "true") == 0) {
        Token token = make_token(TOKEN_TRUE, text, 1, lexer->line);
        return token;
    }
    else if (strcmp(text, "false") == 0) {
        Token token = make_token(TOKEN_FALSE, text, 0, lexer->line);
        return token;
    }
    Token token = make_token(TOKEN_IDENTIFIER, text, 0, lexer->line);
    return token;
}

Token next_token(Lexer *lexer) {
    // skip whitespace
    skip_whitespace(lexer);

    // check each possible token
    switch (lexer->src[lexer->pos]) {
        case '\0':
            return make_token(TOKEN_EOF, NULL, 0, lexer->line);
        case '<':
            if (lexer->src[lexer->pos + 1] == '=') {
                lexer->pos += 2;
                return make_token(TOKEN_LTE, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_LT, NULL, 0, lexer->line);
        case '>':
            if (lexer->src[lexer->pos + 1] == '=') {
                lexer->pos += 2;
                return make_token(TOKEN_GTE, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_GT, NULL, 0, lexer->line);
        case '=':
            if (lexer->src[lexer->pos + 1] == '=') {
                lexer->pos += 2;
                return make_token(TOKEN_EQUALITY, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_ASSIGN, NULL, 0, lexer->line);
        case '!':
            if (lexer->src[lexer->pos + 1] == '=') {
                lexer->pos += 2;
                return make_token(TOKEN_NE, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_NOT, NULL, 0, lexer->line);
        case '|':
            if (lexer->src[lexer->pos + 1] == '|') {
                lexer->pos += 2;
                return make_token(TOKEN_LOGICOR, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_BITOR, NULL, 0, lexer->line);
        case '&':
            if (lexer->src[lexer->pos + 1] == '&') {
                lexer->pos += 2;
                return make_token(TOKEN_LOGICAND, NULL, 0, lexer->line);
            }
            lexer->pos++;
            return make_token(TOKEN_BITAND, NULL, 0, lexer->line);
        case '^':
            lexer->pos++;
            return make_token(TOKEN_XOR, NULL, 0, lexer->line);
        case '+':
            lexer->pos++;
            return make_token(TOKEN_ADD, NULL, 0, lexer->line);
        case '-':
            lexer->pos++;
            return make_token(TOKEN_SUBTRACT, NULL, 0, lexer->line);
        case '*':
            lexer->pos++;
            return make_token(TOKEN_MULTIPLY, NULL, 0, lexer->line);
        case '/':
            lexer->pos++;
            return make_token(TOKEN_DIVIDE, NULL, 0, lexer->line);
        case '(':
            lexer->pos++;
            return make_token(TOKEN_LPAREN, NULL, 0, lexer->line);
        case ')':
            lexer->pos++;
            return make_token(TOKEN_RPAREN, NULL, 0, lexer->line);
        case '{':
            lexer->pos++;
            return make_token(TOKEN_LBRACE, NULL, 0, lexer->line);
        case '}':
            lexer->pos++;
            return make_token(TOKEN_RBRACE, NULL, 0, lexer->line);
        case ',':
            lexer->pos++;
            return make_token(TOKEN_COMMA, NULL, 0, lexer->line);
        case ';':
            lexer->pos++;
            return make_token(TOKEN_SEMICOLON, NULL, 0, lexer->line);
        default:
            if (isdigit(lexer->src[lexer->pos])) {
                return make_token_number(lexer);
            }
            else if (isalpha(lexer->src[lexer->pos]) || lexer->src[lexer->pos] == '_') {
                return make_token_identifier_keyword(lexer);
            }
            else {
                lexer->pos++;
                return make_token(TOKEN_UNKNOWN, NULL, 0, lexer->line);
            }
    }
}