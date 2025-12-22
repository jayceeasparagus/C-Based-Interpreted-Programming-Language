#include "eval.h"
#include <stdint.h>

double eval(ASTNode *node) {
    if(!node) {
        return 0;
    }

    switch (node->type) {
        case AST_NUMBER:
            return node->number;

        case AST_BINARY: {
            double left = eval(node->binary.left);
            double right = eval(node->binary.right);

            switch (node->binary.operand) {
                case TOKEN_ADD:
                    return left + right;
                case TOKEN_SUBTRACT:
                    return left - right;
                case TOKEN_MULTIPLY:
                    return left * right;
                case TOKEN_DIVIDE:
                    return left / right;
                
                case TOKEN_BITAND:
                    return (double)((uint64_t)left & (uint64_t)right);
                case TOKEN_BITOR:
                    return (double)((uint64_t)left | (uint64_t)right);
                case TOKEN_XOR:
                    return (double)((uint64_t)left ^ (uint64_t)right);

                default:
                    printf("ERROR: Unknown binary operator");
                    exit(1);
            }
        }

            case AST_UNARY: {
                double value = eval(node->unary.expression);

                switch (node->unary.operand) {
                    case TOKEN_NOT:
                        return !value;
                    case TOKEN_SUBTRACT:
                        return -value;
                    default:
                        printf("ERROR: Unknown unary operator\n");
                        exit(1);
                }
            }

            case AST_PRINT: {
                double value = eval(node->print.expression);
                printf("%g\n", value);
                return value;
            }

            case AST_STATEMENTS: {
                double last = 0;

                for (int i = 0; i < node->statements.count; ++i) {
                    last = eval(node->statements.statements[i]);
                }

                return last;
            }

            default: {
                printf("ERROR: Unknown ASTNode type\n");
                exit(1);
            }
    }
}