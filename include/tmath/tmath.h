#ifndef TMATH_H
#define TMATH_H

#include <stddef.h>

#define TMATH_AST_INIT {.nodes = NULL, .len = 0, .allocated = 0}

enum tmath_op {
	TMATH_OP_NONE,
	TMATH_OP_EXP = '^',
	TMATH_OP_MUL = '*',
	TMATH_OP_DIV = '/',
	TMATH_OP_ADD = '+',
	TMATH_OP_SUB = '-',
};

struct tmath_ast_node {
	enum tmath_op op;
	double value;
};

struct tmath_ast {
	struct tmath_ast_node* nodes;
	size_t len, allocated;
};

int
tmath_parse(struct tmath_ast* ast, const char* exp);

double
tmath_solve(struct tmath_ast* ast);

#endif // TMATH_H
