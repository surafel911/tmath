#include <stdio.h>

#include <tmath/tmath.h>

int
main(int argc, char* argv[])
{
	char buffer[512];
	struct tmath_ast ast = TMATH_AST_INIT;

	while(1) {
		scanf("%s", buffer);

		if (*buffer == 'q') {
			break;
		}

		if (tmath_parse(&ast, buffer)) {
			puts("Invalid syntax.\n");
			continue;
		}

		printf("%lf\n\n", tmath_solve(&ast));
	}
}
