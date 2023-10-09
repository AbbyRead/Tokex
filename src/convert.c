#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "convert.h"

int main(int argc, char *argv[]) {
	char ch;
	FILE *in, *out;
	check_usage(argc, argv, in, out);

	struct output_flag flag;
	flag.tab = NO;
	flag.space = NO;
	flag.newline  = NO;
	flag.next_nibble = HIGH;

	// values stored in a byte
	struct hexit_pair nibble;
	nibble.high = 0;
	nibble.low = 0;

	while ((ch = getc(in)) != EOF) {
		// Glean Tokex character from input (0xF means invalid)
		char tokex_char = get_tokex(ch, flag);

		// Only process character if it is a valid input
		if (tokex_char != 0xF) {
			int offset; // for tab rounding

			// If at start of output byte
			if (flag.next_nibble == HIGH) {
				if (flag.tab || flag.space || flag.newline) {
					fputc(0, out); // hex 00 byte
					if (flag.newline) fputc(0, out); // extra for nl
					if (flag.tab && !(offset = ftell(out) % TAB_SIZE)) {
						int bytes_to_write = TAB_SIZE - offset;
						for (int i = 0; i < bytes_to_write; ++i) {
							fputc(0, out);
						}
					}
					flag.next_nibble = HIGH;
				} else { // valid alphabetic character
					nibble.high = tokex_char;
					flag.next_nibble = LOW;
				}
				// End high-nibble entry
			} else // to not double-count an input character
			if (flag.next_nibble == LOW) {

				// Check if we need to pad to bytes
				if (flag.tab || flag.space || flag.newline) {
					nibble.low = 0; // padding before actual
					ch = construct_byte(nibble); // pad it
					fputc(ch, out); // output padded preceding byte
					fputc(0, out); // hex 00 actual byte
					if (flag.newline) fputc(0, out); // extra for newline
					if (flag.tab && !(offset = ftell(out) % TAB_SIZE)) {
						int bytes_to_write = TAB_SIZE - offset;
						for (int i = 0; i < bytes_to_write; ++i) {
							fputc(0, out);
						}
					}
				} else { // valid alphabetic character
					nibble.low = tokex_char;
					ch = construct_byte(nibble);
					fputc(ch, out);
				}
				flag.next_nibble = HIGH;
			}
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}

// Should only need to be called on next_nibble LOW since you'd either be
// 	finishing a two character entry or padding an uneven one.
// Don't need to call it if you're just outputting a 00 byte.
char construct_byte(struct hexit_pair nibble) {
	char ch = 0;
	ch &= nibble.low;
	ch &= nibble.high << 4;
	return ch;
}

char get_tokex(const char ch, struct output_flag flag){
	// Clear flags in prep
	flag.tab = NO;
	flag.space = NO;
	flag.newline = NO;

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
			flag.space = YES;
			return 0x0;
		break;

		default:
			fprintf(stderr, "%s%c\n", "Invalid character detected: ", ch);
			return 0xF;
		break;	
	} 
}
