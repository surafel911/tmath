#include <tmath/tmath.h>

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char* _delimiters = "^*/+-";

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
		for (char* op = (char*)_delimiters + index; *op != '\0'; op++) {
			if (*exp == *op) {
				return true;
			}
		}
	}

	return false;
}

static char*
tmath_find_expr(const char* expr, char* pos)
{
	// TODO: Issue with logic (not stopping after finding op).
	for (pos--; (pos != expr && !tmath_is_op(*pos)) || *pos == '.'; pos--);

	return pos;
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

void
tmath_ast_init(struct tmath_ast* ast)
{
	ast->nodes = NULL;
	ast->len = 0;
	ast->allocated = 0;
}

void
tmath_ast_cleanup(struct tmath_ast* ast)
{
	free(ast->nodes);
	ast->len = 0;
	ast->allocated = 0;
}

int
tmath_parse(struct tmath_ast* ast, const char* expr)
{
	char* tok;
	struct tmath_ast_node* node;
	char op;
	size_t len;

	ast->len = 0;

	if (tmath_is_num(expr)) {
		tmath_ast_node_add(ast);
		ast->len++;
		node = ast->nodes;

		node->op = TMATH_OP_NONE;
		sscanf(expr, "%lf", &node->value);

		return 0;
	}

	if (!tmath_has_op(expr, 0)) {
		return -1;
	}

	len = strlen(_delimiters);
	for (int i = 0; i < len; i++) {
		op = _delimiters[i];

		tok = strchr(expr, op);
		while (tok != NULL) {
			tok = tmath_find_expr(expr, tok);
			tmath_ast_node_add(ast);
			node = ast->nodes + (ast->len - 1);

			sscanf(tok, "%lf", &node->value);

			if (ast->len - 1 > 0) {
				node->op = (enum tmath_op)op;
			} else {
				node->op = TMATH_OP_NONE;			

				tmath_ast_node_add(ast);
				node = ast->nodes + (ast->len - 1);

				tok = strchr(tok, op);
				sscanf(++tok, "%lf", &node->value);
				node->op = (enum tmath_op)op;
			}
			
			tok = strchr(tok, op);
		}
	}


	return 0;
}

double
tmath_solve(struct tmath_ast* ast)
{
	double value = 0.0;
/*
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
*/


	return value;
}
