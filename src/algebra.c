#include <tmath/algebra.h>

#include <math.h>

#include <tmath/tmath.h>
#include <tmath/tmath_i.h>

static void
tmath_algebra_solve_op(double* values, enum tmath_op op)
{
	switch (op) {
	case TMATH_OP_MUL:
		*values = *values * *(values + 1);
		break;
	case TMATH_OP_DIV:
		*values = *values / *(values + 1);
		break;
	case TMATH_OP_ADD:
		*values = *values + *(values + 1);
		break;
	case TMATH_OP_SUB:
		*values = *values - *(values + 1);
		break;
	default:
		break;
	}
}

static void
tmath_algebra_solve_exp(struct tmath_ast* ast)
{
	for (int i = ast->len - 2; i >= 0; i--) {
		if (ast->ops[i] == TMATH_OP_EXP) {
			ast->values[i] = pow(ast->values[i], ast->values[i + 1]);
			tmath_ast_remove_node(ast, i);
		}
	}
}

static void
tmath_algebra_solve_arithmetic(struct tmath_ast* ast, enum tmath_op op)
{
	for (int i = 0; i < ast->len - 1;) {
		if (ast->ops[i] == op) {
			tmath_algebra_solve_op(ast->values + i, op);
			tmath_ast_remove_node(ast, i);

			i = 0;
		} else {
			i++;
		}
	}

}

void
tmath_algebra_solve(struct tmath_ast* ast)
{
	tmath_algebra_solve_exp(ast);
	tmath_algebra_solve_arithmetic(ast, TMATH_OP_MUL);
	tmath_algebra_solve_arithmetic(ast, TMATH_OP_DIV);
	tmath_algebra_solve_arithmetic(ast, TMATH_OP_ADD);
	tmath_algebra_solve_arithmetic(ast, TMATH_OP_SUB);
}
