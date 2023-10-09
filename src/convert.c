#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_usage(int argc, char **argv, FILE *in, FILE *out);

struct hexit_pair {
	unsigned int high : 4;
	unsigned int low : 4;
};

struct output_flag {
	unsigned int tab : 1;
	unsigned int newline  : 1;
	unsigned int nibble_counter : 1;
};

int main(int argc, char *argv[]) {
	char ch;
	FILE *in, *out;
	check_usage(argc, argv, in, out);

	struct output_flag flag;
	#define NO  0
	#define YES 1
	#define HIGH 0
	#define LOW  1
	flag.tab = NO;
	flag.newline  = NO;
	flag.nibble_counter = HIGH;

	// values stored in a byte
	struct hexit_pair nibble;
	nibble.high = 0;
	nibble.low = 0;

	while ((ch = getc(in)) != EOF) {
		if (ch )
		if (flag.nibble_counter == HIGH) {
			nibble.high = get_tokex(ch, flag);
		} else {
			nibble.low  = get_tokex(ch, flag);
		}
		if (flag.)

		if (nibble.high != 0xF) {}
		if (flag.tab == YES) {}
		if (flag.nl  == YES) {}
	}
	
	return 0;
}

char get_tokex(const char ch, struct output_flag flag){
	switch(ch) {
		case 'A':
		case 'a':
			return 0xA;
		break;

		case 'I':
		case 'i':
			return 0x1;
		break;
		
		case 'U':
		case 'u':
			return 0x2;
		break;
		
		case 'E':
		case 'e':
			return 0xE;
		break;
		
		case 'O':
		case 'o':
			return 0x6;
		break;
		
		case 'P':
		case 'p':
			return 0xB;
		break;
		
		case 'T':
		case 't':
			return 0xD;
		break;
		
		case 'K':
		case 'k':
			return 0xC;
		break;
		
		case 'M':
		case 'm':
			return 0x8;
		break;
		
		case 'N':
		case 'n':
			return 0x9;
		break;
		
		case 'L':
		case 'l':
			return 0x7;
		break;
		
		case 'S':
		case 's':
			return 0x5;
		break;
		
		case 'J':
		case 'j':
			return 0x4;
		break;
		
		case 'W':
		case 'w':
			return 0x3;
		break;
		
		case '\n':
			flag.newline = YES;
			return 0x0;
		break;

		case '\t':
			flag.tab = YES;
			return 0x0;
		break;
		
		case ' ':
		case '.':
			return 0x0;
		break;

		default:
			fprintf(stderr, "%s%c\n", "Invalid character detected: ", ch);
			return 0xF;
		break;	
	} 
}

int check_usage(int argc, char **argv, FILE *in, FILE *out) {
	if (argc != 3) {
		fprintf(stderr, "Usage: ./%s <in> <out>\n", *argv[0]);
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