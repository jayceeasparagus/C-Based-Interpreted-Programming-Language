#include "ast.h"

static void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }
}

ASTNode *ast_number(double value) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_NUMBER;
    astnode->number = value;
    return astnode;
}

ASTNode *ast_boolean(double boolean) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_BOOLEAN;
    astnode->number = boolean;
    return astnode;
}

ASTNode *ast_identifier(const char *name) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_IDENTIFIER;
    astnode->identifier = name;
    return astnode;
}

ASTNode *ast_binary(TokenType operand, ASTNode *left, ASTNode *right) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_BINARY;
    astnode->binary.operand = operand;
    astnode->binary.left = left;
    astnode->binary.right = right;
    return astnode;
}

ASTNode *ast_unary(TokenType operand, ASTNode *expression) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_UNARY;
    astnode->unary.operand = operand;
    astnode->unary.expression = expression;
    return astnode;
}

ASTNode *ast_print(ASTNode *expression) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_PRINT;
    astnode->print.expression = expression;
    return astnode;
}

ASTNode *ast_statements(ASTNode **statements, int count) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_STATEMENTS;
    astnode->statements.statements = statements;
    astnode->statements.count = count;
    return astnode;
}

ASTNode *ast_assign(const char *name, ASTNode *value) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_ASSIGN;
    astnode->assign.name = name;
    astnode->assign.value = value;
    return astnode;
}

ASTNode *ast_declaration(const char *name, TokenType type, ASTNode *value) {
    ASTNode *astnode = malloc(sizeof(ASTNode));
    astnode->type = AST_DECLARATION;
    astnode->declaration.name = name;
    astnode->declaration.type = type;
    astnode->declaration.value = value;
    return astnode;
}

ASTNode *ast_comparison(TokenType operand, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_COMPARISON;
    node->comparison.operand = operand;
    node->comparison.left = left;
    node->comparison.right = right;
    return node;
}

ASTNode *ast_if_else(ASTNode *condition, ASTNode *then_statements, ASTNode *else_statements) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF_ELSE;
    node->if_else.condition = condition;
    node->if_else.then_statements = then_statements;
    node->if_else.else_statements = else_statements;
    return node;
}

ASTNode *ast_module(const char *name, char **inputs, int input_count, char **outputs, int output_count, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_MODULE;
    node->module.name = name;
    node->module.inputs = inputs;
    node->module.input_count = input_count;
    node->module.outputs = outputs;
    node->module.output_count = output_count;
    node->module.body = body;
    return node;
}

ASTNode *ast_call(const char *name, ASTNode **args, int arg_count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_CALL;
    node->call.name = name;
    node->call.args = args;
    node->call.arg_count = arg_count;
    return node;
}

ASTNode *ast_while_loop(ASTNode *condition, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_WHILE;
    node->while_loop.condition = condition;
    node->while_loop.body = body;
    return node;
}

void ast_print_tree(ASTNode *node, int indent) {
    if (!node) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    switch (node->type) {
        case AST_NUMBER:
            printf("%.2f\n", node->number);
            break;
        case AST_BOOLEAN:
            printf("%.2f\n", node->number);
            break;
        case AST_IDENTIFIER:
            printf("%s\n", node->identifier);
            break;
        case AST_BINARY:
            printf("%s\n", token_type_name(node->binary.operand));
            ast_print_tree(node->binary.left, indent + 1);
            ast_print_tree(node->binary.right, indent + 1);
            break;
        case AST_UNARY:
            printf("%s\n", token_type_name(node->unary.operand));
            ast_print_tree(node->unary.expression, indent + 1);
            break;
        case AST_PRINT:
            printf("PRINT\n");
            ast_print_tree(node->print.expression, indent + 1);
            break;
        case AST_STATEMENTS:
            printf("STATEMENTS\n");
            for (int i = 0; i < node->statements.count; ++i) {
                ast_print_tree(node->statements.statements[i], indent + 1);
            }
            break;
        case AST_ASSIGN:
            printf("ASSIGN\n");
            ast_print_tree(node->assign.value, indent + 1);
            break;
        case AST_DECLARATION:
            printf("DECLARATION\n");
            ast_print_tree(node->declaration.value, indent + 1);
            break;
        case AST_COMPARISON:
            printf("%s\n", token_type_name(node->comparison.operand));
            ast_print_tree(node->comparison.left, indent + 1);
            ast_print_tree(node->comparison.right, indent + 1);
            break;
        case AST_IF_ELSE:
            printf("IF\n");
            for (int i = 0; i < indent + 1; ++i) {
                printf(" ");
            }
            printf("CONDITION\n");
            ast_print_tree(node->if_else.condition, indent + 2);

            for (int i = 0; i < indent + 1; ++i) {
                printf("  ");
            }
            printf("THEN\n");
            ast_print_tree(node->if_else.then_statements, indent + 2);
            
            if (node->if_else.else_statements) {
                for (int i = 0; i < indent + 1; ++i) {
                    printf("  ");
                }
                printf("ELSE\n");
                ast_print_tree(node->if_else.else_statements, indent + 2);
            }
            break;
        case AST_WHILE:
            printf("WHILE\n");

            for (int i = 0; i < indent + 1; ++i) {
                printf("  ");
            }
            printf("CONDITION\n");
            ast_print_tree(node->while_loop.condition, indent + 2);

            for (int i = 0; i < indent + 1; ++i) {
                printf("  ");
            }
            printf("BODY\n");
            ast_print_tree(node->while_loop.body, indent + 2);
            break;
        case AST_MODULE:
            print_indent(indent);
            printf("MODULE %s\n", node->module.name);

            print_indent(indent + 1);
            printf("INPUTS\n");
            for (int i = 0; i < node->module.input_count; ++i) {
                print_indent(indent + 2);
                printf("%s\n", node->module.inputs[i]);
            }

            print_indent(indent + 1);
            printf("OUTPUTS\n");
            for (int i = 0; i < node->module.output_count; ++i) {
                print_indent(indent + 2);
                printf("%s\n", node->module.outputs[i]);
            }

            print_indent(indent + 1);
            printf("BODY\n");
            ast_print_tree(node->module.body, indent + 2);
            break;
        case AST_CALL:
            print_indent(indent);
            printf("CALL %s\n", node->call.name);
            
            print_indent(indent + 1);
            printf("ARGUMENTS\n");
            for (int i = 0; i < node->call.arg_count; ++i) {
                ast_print_tree(node->call.args[i], indent + 2);
            }
            break;
    }
}