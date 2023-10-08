#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *in, *out;
	char ch;
	if (argc != 3) {
		printf("%s", "Usage: ./convert <in> <out>\n");
		exit(1);
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open %s.\n", argv[1]);
		exit(1);
	}

	if ((out = fopen(argv[2], "wb")) == NULL) {
		printf("Cannot open %s.\n", argv[1]);
		exit(1);
	}

	while ((ch = getc(in)) != EOF) {
		putc(ch, out);
	}
	
	return 0;
}