#include "eval.h"
#include "env.h"
#include <stdint.h>

#define MAX_MODULES 128
#define MAX_OUTPUTS 16

static ModuleEntry modules[MAX_MODULES];
static int module_count = 0;

ASTNode *find_module(const char *name) {
    for (int i = 0; i < module_count; ++i) {
        if (strcmp(modules[i].name, name) == 0) {
            return modules[i].module;
        }
    }
    printf("ERROR: Unknown module call '%s'", name);
    exit(1);
}

Value eval(ASTNode *node) {
    if(!node) {
        return value_number(0);
    }

    switch (node->type) {
        case AST_NUMBER:
            return value_number(node->number);

        case AST_IDENTIFIER:
            return env_get(node->identifier);

        case AST_BOOLEAN:
            return value_boolean(node->number);
      
        case AST_BINARY: {
            Value left = eval(node->binary.left);
            Value right = eval(node->binary.right);

            switch (node->binary.operand) {
                case TOKEN_ADD:
                    return value_number(left.number + right.number);
                case TOKEN_SUBTRACT:
                    return value_number(left.number - right.number);
                case TOKEN_MULTIPLY:
                    return value_number(left.number * right.number);
                case TOKEN_DIVIDE:
                    return value_number(left.number / right.number);
                
                case TOKEN_BITAND:
                    return value_number((double)((uint64_t)left.number & (uint64_t)right.number));
                case TOKEN_BITOR:
                    return value_number((double)((uint64_t)left.number | (uint64_t)right.number));
                case TOKEN_XOR:
                    return value_number((double)((uint64_t)left.number ^ (uint64_t)right.number));
                case TOKEN_LOGICAND:
                    return value_boolean(left.boolean && right.boolean);
                case TOKEN_LOGICOR:
                    return value_boolean(left.boolean || right.boolean);

                default:
                    printf("ERROR: Unknown binary operator\n");
                    exit(1);
            }
        }

            case AST_UNARY: {
                Value value = eval(node->unary.expression);

                switch (node->unary.operand) {
                    case TOKEN_SUBTRACT:
                        return value_number(-value.number);
                    case TOKEN_NOT:
                        return value_boolean(!value.boolean);
                    default:
                        printf("ERROR: Unknown unary operator\n");
                        exit(1);
                }
            }

            case AST_PRINT: {
                Value value = eval(node->print.expression);
                if (value.type == VAL_NUMBER) {
                    printf("%g\n", value.number);
                }
                else if (value.type == VAL_BOOL) {
                    if (value.boolean == 1) {
                        printf("true\n");
                    }
                    else {
                        printf("false\n");
                    }
                }
                return value;
            }

            case AST_STATEMENTS: {
                Value last = value_number(0);

                for (int i = 0; i < node->statements.count; ++i) {
                    last = eval(node->statements.statements[i]);
                }

                return last;
            }


            case AST_DECLARATION: {
                Value value = eval(node->declaration.value);

                env_set(node->declaration.name, value);

                return value;
            }

            case AST_ASSIGN: {
                Value value = eval(node->assign.value);
                env_set(node->assign.name, value);
                return value;
            }

            case AST_COMPARISON: {
                Value left = eval(node->comparison.left);
                Value right = eval(node->comparison.right);

                switch (node->comparison.operand) {
                    case TOKEN_EQUALITY:
                        return value_boolean(left.number == right.number);
                    case TOKEN_NE:
                        return value_boolean(left.number != right.number);
                    case TOKEN_LT:
                        return value_boolean(left.number < right.number);
                    case TOKEN_GT:
                        return value_boolean(left.number > right.number);
                    case TOKEN_LTE:
                        return value_boolean(left.number <= right.number);
                    case TOKEN_GTE:
                        return value_boolean(left.number >= right.number);
                    default:
                        printf("ERROR: Unknown comparison operator\n");
                        exit(1);
                }
            }

            case AST_IF_ELSE: {
                Value condition = eval(node->if_else.condition);

                if (condition.boolean) {
                    return eval(node->if_else.then_statements);
                }
                else if (node->if_else.else_statements) {
                    return eval(node->if_else.else_statements);
                }

                return value_number(0);
            }

            case AST_WHILE: {
                Value result = value_number(0);

                while (eval(node->while_loop.condition).boolean) {
                    result = eval(node->while_loop.body);
                }

                return result;
            }

            case AST_MODULE: 
                modules[module_count++] = (ModuleEntry){node->module.name, node};
                return value_number(0);

            case AST_CALL: {
                ASTNode *module = find_module(node->call.name);

                Env *module_env = push_env();

                for (int i = 0; i < module->module.input_count; ++i) {
                    Value v = eval(node->call.args[i]);
                    env_set(module->module.inputs[i], v);
                }

                eval(module->module.body);

                Value outputs[MAX_OUTPUTS];
                if (module->module.output_count > MAX_OUTPUTS) {
                    printf("ERROR: Module has too many outputs, max amount of outputs is 16.  Module had %d outputs", module->module.output_count);
                }
                for (int i = 0; i < module->module.output_count; ++i) {
                    outputs[i] = env_get_from(module_env, module->module.outputs[i]);
                }

                pop_env();
                
                for (int i = 0; i < module->module.output_count; ++i) {
                    ASTNode *output_arg = node->call.args[module->module.input_count + i];
                    env_set(output_arg->identifier, outputs[i]);
                }

                return value_number(0);
            }

            default: {
                printf("ERROR: Unknown ASTNode type\n");
                exit(1);
            }
    }
}