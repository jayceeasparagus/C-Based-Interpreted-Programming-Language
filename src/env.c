#include "env.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VARS 256

static Variable variables[MAX_VARS];
static int variable_count = 0;

Value value_number(double number) {
    return (Value){.type = VAL_NUMBER, .number = number};
}

Value value_boolean(double boolean) {
    return (Value){.type = VAL_BOOL, .boolean = boolean};
}

Value env_get(const char *name) {
    for (int i = 0; i < variable_count; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("ERROR: Undefined variable: %s\n", name);
    exit(1);
}

void env_set(const char *name, Value value) {
    for (int i = 0; i < variable_count; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    variables[variable_count++] = (Variable){(char*)name, value};
}