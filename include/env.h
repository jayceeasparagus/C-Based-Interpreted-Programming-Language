#include "ast.h"

#ifndef ENV_H
#define ENV_H

typedef struct Env Env;

typedef enum {
    VAL_NUMBER,
    VAL_BOOL
} ValueType;

typedef struct {
    ValueType type;
    union {
        double number;
        int boolean;
    };
} Value;

typedef struct {
    const char *name;
    ASTNode *module;
} ModuleEntry;

struct Env {
    char *names[128];
    Value values[128];
    int count;
    Env *parent;
};

Value value_number(double number);
Value value_boolean(double boolean);

Value env_get(const char *name);
void env_set(const char *name, Value value);

Env *push_env();

void pop_env();

void env_init(void);

Env *env_current();

void env_set_current(Env *env);

Value env_get_from(Env *env, const char *name);

#endif