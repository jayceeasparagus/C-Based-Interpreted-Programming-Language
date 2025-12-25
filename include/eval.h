#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include "env.h"

ASTNode *find_module(const char *name);

Value eval(ASTNode *node);

#endif