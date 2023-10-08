#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

	char cbyte = 0;
	bool nibble = 0;
	while ((ch = getc(in)) != EOF) {
		if (nibble == 0) {
			nibble = 1;
			switch(ch) {
				case 'A':
				case 'a':
					cbyte = 0xA0;
				break;
				case 'I':
				case 'i':
					cbyte = 0x10;
				break;
				
				case 'U':
				case 'u':
					cbyte = 0x20;
				break;
				
				case 'E':
				case 'e':
					cbyte = 0xE0;
				break;
				
				case 'O':
				case 'o':
					cbyte = 0x60;
				break;
				
				case 'P':
				case 'p':
					cbyte = 0xB0;
				break;
				
				case 'T':
				case 't':
					cbyte = 0xD0;
				break;
				
				case 'K':
				case 'k':
					cbyte = 0xC0;
				break;
				
				case 'M':
				case 'm':
					cbyte = 0x80;
				break;
				
				case 'N':
				case 'n':
					cbyte = 0x90;
				break;
				
				case 'L':
				case 'l':
					cbyte = 0x70;
				break;
				
				case 'S':
				case 's':
					cbyte = 0x50;
				break;
				
				case 'J':
				case 'j':
					cbyte = 0x40;
				break;
				
				case 'W':
				case 'w':
					cbyte = 0x30;
				break;
				
				case '\n':
					cbyte = 0x00;
					nibble = 0;
				break;
				
				case ' ':
				case '.':
					cbyte = 0xA0;
				break;

				default:
					fprintf(stderr, "%s%c\n", "Invalid character detected: ", ch);
				break;	
			} 
		} else {
			switch(ch) {
				case 'A':
				case 'a':
			

			}
		}
		putc(ch, out);
	}
	
	return 0;
}