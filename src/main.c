#include <stdio.h>

#include <tmath/tmath.h>

int
main(int argc, char* argv[])
{
	char buffer[512];

	while(1) {
		scanf("%s", buffer);
		if (*buffer == 'q') {
			break;
		}

		puts("");
		tmath_solve(buffer);
	}
}
