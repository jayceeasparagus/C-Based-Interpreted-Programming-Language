#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include "env.h"

Value eval(ASTNode *node);

#endif