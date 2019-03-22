#ifndef TMATH_TMATH_I_H
#define TMATH_TMATH_I_H

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include <tmath/tmath.h>

static inline bool
tmath_is_num(const char* expr)
{
	for (; *expr != '\0'; expr++) {
		if (*expr == '.') {
			continue;
		}

		if (!isdigit(*expr)) {
			return false;
		}
	}

	return true;
}

static inline bool
tmath_is_op(char c)
{
	switch (c) {
	case TMATH_OP_EXP:
	case TMATH_OP_MUL:
	case TMATH_OP_DIV:
	case TMATH_OP_ADD:
	case TMATH_OP_SUB:
		return true;
	}

	return false;
}

static inline void
tmath_ast_remove_node(struct tmath_ast* ast, const int index)
{
	memmove(ast->ops + index, ast->ops + index + 1,
		sizeof(*ast->ops) * (ast->len - index - 1));
	memmove(ast->values + index + 1, ast->values + index + 2,
		sizeof(*ast->values) * (ast->len - index - 2));

	ast->len--;
}

#endif // TMATH_TMATH_I_H
