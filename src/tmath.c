#include <tmath/tmath.h>

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*x))

static const char* _delimiters[] = {
	"^",
	"*",
	"/",
	"+",
	"-",
};

static bool
tmath_is_num(const char* exp)
{
	for (; *exp != '\0'; exp++) {
		if (*exp == '.') {
			continue;
		}

		if (!isdigit(*exp)) {
			return false;
		}
	}

	return true;
}

static bool
tmath_has_op(const char* exp, int index)
{
	for (; *exp != '\0'; exp++) {
		for (int i = index; i < ARRAY_SIZE(_delimiters); i++) {
			if (*exp == *_delimiters[i]) {
				return true;
			}
		}
	}

	return false;
}

static void
tmath_ast_node_add(struct tmath_ast* ast)
{
	if (ast->len < ast->allocated) {
		ast->len++;
	} else {
		ast->len++;
		ast->allocated++;
		ast->nodes = realloc(ast->nodes, sizeof(*(ast->nodes)) * ast->allocated);
	}
}

int
tmath_parse(struct tmath_ast* ast, const char* exp)
{
	char* tok;
	const char* op;

	if (tmath_is_num(exp)) {
		tmath_ast_node_add(ast);

		ast->nodes[0].op = TMATH_OP_NONE;
		sscanf(exp, "%lf", &ast->nodes[0].value);

		return 0;
	}

	if (!tmath_has_op(exp, 0)) {
		return -1;
	}

	for (int i = 0; i < ARRAY_SIZE(_delimiters); i++) {
		op = _delimiters[i];
		tok = strtok((char*)exp, op);

		if (tmath_has_op(exp, i)) {
			// TODO: Only find number in expression
		} else {
			//TODO: Add number to AST.
		}
	}

	return 0;
}

double
tmath_solve(struct tmath_ast* ast)
{
	double value = 0.0;

	value = ast->nodes[0].value;

	for (int i = 1; i < ast->len; i++) {
		switch (ast->nodes[i].op) {
		case TMATH_OP_EXP:
			value = pow(value, ast->nodes[i].value);
			break;
		case TMATH_OP_MUL:
			value *= ast->nodes[i].value;
			break;
		case TMATH_OP_DIV:
			value /= ast->nodes[i].value;
			break;
		case TMATH_OP_ADD:
			value += ast->nodes[i].value;
			break;
		case TMATH_OP_SUB:
			value -= ast->nodes[i].value;
			break;
		default:
			break;	
		}
	}

	return value;
}
