#ifndef TMATH_H
#define TMATH_H

#include <stddef.h>

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

void
tmath_ast_init(struct tmath_ast* ast);

void
tmath_ast_cleanup(struct tmath_ast* ast);

int
tmath_parse(struct tmath_ast* ast, const char* expr);

double
tmath_solve(struct tmath_ast* ast);

#endif // TMATH_H
