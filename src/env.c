#include "env.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Env *current_env = NULL;

void env_init() {
    current_env = malloc(sizeof(Env));
    current_env->count = 0;
    current_env->parent = NULL;
}

Value value_number(double number) {
    return (Value){.type = VAL_NUMBER, .number = number};
}

Value value_boolean(double boolean) {
    return (Value){.type = VAL_BOOL, .boolean = boolean};
}

Value env_get(const char *name) {
    for (Env *env = current_env; env != NULL; env = env->parent) {
        for (int i = env->count - 1; i >= 0; i--) {
            if (strcmp(env->names[i], name) == 0) {
                return env->values[i];
            }
        }
    }

    printf("ERROR: Unknown variable\n");
    exit(1);
}

void env_set(const char *name, Value value) {
    Env *env = current_env;

    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->names[i], name) == 0) {
            env->values[i] = value;
            return;
        }
    }

    if (env->count >= MAX_VARS) {
        printf("ERROR: Max Variables for scope\n");
        exit(1);
    }

    env->names[env->count] = strdup(name);
    env->values[env->count] = value;
    env->count++;
}

Env *push_env() {
    Env *new_env = malloc(sizeof(Env));
    new_env->count = 0;
    new_env->parent = current_env;
    current_env = new_env;
    return new_env;
}

void pop_env() {
    Env *old_env = current_env;
    current_env = current_env->parent;
    free(old_env);
}

Env *env_current() {
    return current_env;
}

void env_set_current(Env *env) {
    current_env = env;
}

Value env_get_from(Env *env, const char *name) {
    for (Env *e = env; e != NULL; e = e->parent) {
        for (int i = 0; i < e->count; i++) {
            if (strcmp(e->names[i], name) == 0) {
                return e->values[i];
            }
        }
    }
    printf("ERROR: Undefined variable '%s'\n", name);
    exit(1);
}