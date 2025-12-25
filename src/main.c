#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "eval.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (!file) {
        printf("ERROR: Could not open file '%s'", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        printf("ERROR: Out of memory\n");
        exit(1);
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("ERROR: Format is 'jh <filename.jh>'\n");
        return 1;
    }

    char *source = read_file(argv[1]);

    Lexer lexer = {.src = source, .pos = 0, .line = 1};

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *program = parse_program(&parser);

    env_init();
    eval(program);

    free(source);

    return 0;
}