#ifndef ENV_H
#define ENV_H

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
    char *name;
    Value value;
} Variable;

Value value_number(double number);
Value value_boolean(double boolean);

Value env_get(const char *name);
void env_set(const char *name, Value value);

#endif