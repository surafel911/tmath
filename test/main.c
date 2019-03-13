#include <stdio.h>
#include <string.h>

#include <tmath/tmath.h>

int
main(int argc, char* argv[])
{
	char buffer[512];
	struct tmath_ast ast;

	tmath_ast_init(&ast);

	while(1) {
		fgets(buffer, sizeof(buffer), stdin);
		*strchr(buffer, '\n') = '\0';

		if (*buffer == 'q') {
			break;
		}

		if (tmath_parse(&ast, buffer)) {
			puts("Invalid syntax.\n");
			continue;
		}

		printf("%lf\n\n", tmath_solve(&ast));
	}

	tmath_ast_cleanup(&ast);
}
