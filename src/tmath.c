#include <tmath/tmath.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static const char* _delimiters[] = {
	"^",
	"*/",
	"+-",
};

enum tmath_op {
	TMATH_OP_EXP = '^',
	TMATH_OP_MUL = '*',
	TMATH_OP_DIV = '/',
	TMATH_OP_ADD = '+',
	TMATH_OP_SUB = '-',
};

struct tmath_ast_node {
	struct tmath_ast_node* ast;
	double lhs, rhs;
	enum tmath_op op;
};

static bool
tmath_has_op(const char* exp)
{
	const char* tmp;
	while (*tmp > '\0') {
		switch (*tmp) {
		case TMATH_OP_EXP:
		case TMATH_OP_MUL:
		case TMATH_OP_DIV:
		case TMATH_OP_ADD:
		case TMATH_OP_SUB:
			return true;
			break;
		}
	}

	return false;
}

static struct tmath_ast_node*
tmath_parse(const char* exp)
{
	char* tok;
	const char* op;
	struct tmath_ast_node* ast = NULL;
	size_t len;

	// TODO: strtok likely replaces delimiters with '\0'. Find a way around that

	len = strlen(exp);
	for (int i = 0; i < sizeof(_delimiters); i++) {
		op = _delimiters[i];
		tok = strtok((char*)exp, op);

		while (tok != NULL) {
			printf("%s: %s\n", op, tok);
			tok = strtok(NULL, op);
		}
	}

	return ast;
}

double
tmath_solve(const char* exp)
{
	struct tmath_ast_node* ast;

	ast = tmath_parse(exp);

	return 0.0;
}
