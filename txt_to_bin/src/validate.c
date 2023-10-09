#include "convert.h"

int check_usage(int argc, char **argv, FILE *in, FILE *out) {
	if (argc != 3) {
		fprintf(stderr, "Usage: ./%s <in> <out>\n", argv[0]);
		exit(1);
	}

	if ((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Cannot open %s.\n", argv[1]);
		exit(1);
	}

	if ((out = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "Cannot open %s.\n", argv[1]);
		exit(1);
	}
	return 0;
}