
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(*x))

#define TMATH_AST_INIT {.nodes = NULL, .len = 0}

static const char* _delimiters[] = {
	"^",
	"*",
	"/",
	"+",
	"-",
};

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
	size_t len;
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
	ast->nodes = realloc(ast->nodes, sizeof(*(ast->nodes)));
	ast->len++;
}

static void
tmath_parse(struct tmath_ast* ast, const char* exp)
{
	char* tok;
	const char* op;

	if (tmath_is_num(exp)) {
		tmath_ast_node_add(ast);

		ast->nodes[0].op = TMATH_OP_NONE;
		sscanf(exp, "%lf", &ast->nodes[0].value);

		return;
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
}

double
tmath_solve(const char* exp)
{
	struct tmath_ast ast = TMATH_AST_INIT;
	double value = 0.0;

	tmath_parse(&ast, exp);

	value = ast.nodes[0].value;

	for (int i = 1; i < ast.len; i++) {
		switch (ast.nodes[i].op) {
		case TMATH_OP_EXP:
			value = pow(value, ast.nodes[i].value);
			break;
		case TMATH_OP_MUL:
			value *= ast.nodes[i].value;
			break;
		case TMATH_OP_DIV:
			value /= ast.nodes[i].value;
			break;
		case TMATH_OP_ADD:
			value += ast.nodes[i].value;
			break;
		case TMATH_OP_SUB:
			value -= ast.nodes[i].value;
			break;
		default:
			puts("Invalid op.");
			abort();
			break;
		}
	}

	free(ast.nodes);

	return value;
}
