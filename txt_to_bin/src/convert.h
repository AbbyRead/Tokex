#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAB_SIZE 4 // (bytes)

struct hexit_pair {
	unsigned int high : 4;
	unsigned int low : 4;
};

struct output_flag {
	unsigned int tab : 1;
	unsigned int space : 1;
	unsigned int newline  : 1;
	unsigned int next_nibble : 1;
};
	// .tab or .newline
	#define NO  0
	#define YES 1

	// .nibble_counter
	#define HIGH 0
	#define LOW  1

// Globals
FILE *in, *out;

int check_usage(int argc, char **argv);
char get_tokex(const char ch, struct output_flag *flag);
char construct_byte(struct hexit_pair nibble);

#endif