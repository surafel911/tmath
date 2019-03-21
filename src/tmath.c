#include <tmath/tmath.h>

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(x)	(sizeof(x)/sizeof(*x))

static const char* _operators = "^*/+-";

static bool
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

static bool
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

static bool
tmath_has_op(const char* expr)
{
	for (; *expr != '\0'; expr++) {
		for (const char* op = _operators; *op != '\0'; op++) {
			if (*expr == *op) {
				return true;
			}
		}
	}

	return false;
}

static const char*
tmath_next_op(const char* expr)
{
	for (; *expr != '\0' && !tmath_is_op(*expr); ++expr);

	return expr;
}

static void
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

static void
tmath_ast_solve(struct tmath_ast* ast, int index)
{
	double x, y;

	x = ast->values[index];
	y = ast->values[index + 1];
	switch (ast->ops[index]) {
	case TMATH_OP_EXP:
		ast->values[index] = pow(x, y);
		break;
	case TMATH_OP_MUL:
		ast->values[index] = x * y;
		break;
	case TMATH_OP_DIV:
		ast->values[index] = x / y;
		break;
	case TMATH_OP_ADD:
		ast->values[index] = x + y;
		break;
	case TMATH_OP_SUB:
		ast->values[index] = x - y;
		break;
	default:
		break;
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
	for (int i = 0; i < ARRAY_SIZE(_operators); i++) {
		for (int j = 0; j < ast->len - 1; j++) {
			if (ast->ops[j] == _operators[i]) {
				tmath_ast_solve(ast, j);

				memmove(ast->ops + j, ast->ops + j + 1, sizeof(*ast->ops) * (ast->len - j - 1));
				memmove(ast->values + j + 1, ast->values + j + 2, sizeof(*ast->values) * (ast->len - j - 2));

				j = 0;
				ast->len -= 1;
			}
		}
	}

	return *ast->values;
}
