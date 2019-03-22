#include <tmath/tmath.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <tmath/algebra.h>
#include <tmath/tmath_i.h>

static inline bool
tmath_has_op(const char* expr)
{
	for (; *expr != '\0'; expr++) {
		if (tmath_is_op(*expr)) {
			return true;
		}
	}

	return false;
}

static inline const char*
tmath_next_op(const char* expr)
{
	for (; *expr != '\0' && !tmath_is_op(*expr); ++expr);

	return expr;
}

static inline void
tmath_ast_add(struct tmath_ast* ast)
{
	if (ast->len < ast->allocated) {
		ast->len++;
	} else {
		ast->len++;
		ast->allocated++;
		ast->ops = realloc(ast->ops, sizeof(*ast->ops) * ast->allocated);
		ast->values = realloc(ast->values, sizeof(*ast->values) * ast->allocated);

		*(ast->ops + ast->len - 1) = TMATH_OP_NONE;
		*(ast->values + ast->len - 1) = 0.0;
	}
}

void
tmath_ast_init(struct tmath_ast* ast)
{
	ast->ops = NULL;
	ast->values = NULL;
	ast->len = 0;
	ast->allocated = 0;
}

void
tmath_ast_cleanup(struct tmath_ast* ast)
{
	free(ast->ops);
	free(ast->values);
	ast->ops = NULL;
	ast->values = NULL;
	ast->len = 0;
	ast->allocated = 0;
}

int
tmath_parse(struct tmath_ast* ast, const char* expr)
{
	double* value;
	enum tmath_op* op;

	ast->len = 0;

	if (tmath_is_num(expr)) {
		tmath_ast_add(ast);
		op = ast->ops;
		value = ast->values;

		*op = TMATH_OP_NONE;
		sscanf(expr, "%lf", value);

		return 0;
	}

	if (!tmath_has_op(expr)) {
		return -1;
	}

	while (true) {
		tmath_ast_add(ast);
		op = (ast->ops + ast->len - 1);
		value = (ast->values + ast->len - 1);

		sscanf(expr, "%lf", value);

		expr = tmath_next_op(expr);

		if (*expr != '\0') {
			*op = (enum tmath_op)(*expr);
			++expr;
		} else {
			*op = TMATH_OP_NONE;
			break;
		}
	}

	return 0;
}

double
tmath_solve(struct tmath_ast* ast)
{
	tmath_algebra_solve(ast);	
	
	return *ast->values;
}
