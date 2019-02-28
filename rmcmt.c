 /* rmct.c */
 /* Abraham Schultz */
 /* Last edited 2/19/2019 */
 /* This is a c program that removes comments from a c file
    I got a lot of help from a program found at https://www.msully.net/files/decomment.c written by Mike Sullivan
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define BUF_SIZE 64
#define OUT 0

/* function declaration  */
int decomment(FILE *f);
int lineCounter = 0;

int main(int argc, char *argv[]) {

	FILE* f;
	// create array for input string
        char s[BUF_SIZE];
	// take input from keyboard
	scanf("%s", s);
	// open file, f = NULL if can not open file stream
	 f  = fopen (s, "rw");

	//check if file is open
	if (f == NULL){
	printf ("\n Incorrect file name \n");
	return EXIT_FAILURE;
       }
         else

	// call function to de-comment file
	decomment(f);
	// close file stream
	fclose(f);
	return 0;
} // end main

int decomment(FILE *f) {
	int escape; /* escape char is up */
	int in_comment; /* whether it is currently inside a comment */
	int in_quote; /* whether it is currently inside quotes */
	char quote_type; /* whether it's a double or single quote */
	int c, tmp;
	/* sets all states to 0 on first pass */
	c = escape = quote_type = in_quote = in_comment = OUT;
	while ((c = getc(f)) != EOF) {
		/* count lines */
		if (c == '\n') {
		lineCounter ++ ;
                }
		/* check for beginning  of c comment*/
		if (!in_quote && c == '/') {
			if ((tmp = getc(f)) == '*')
				in_comment = 1;
			else
				ungetc(tmp, f);
		}
		/* checks for end of c comment  */
		if (in_comment && c == '*') {
			if ((tmp = getc(f)) == '/') {
				in_comment = OUT;
				continue;
			} else
				ungetc(tmp, f);
		}

		/* check to see if we are inside a quote   */
		if (in_quote && !escape && c == quote_type)
			quote_type = in_quote = OUT;
		else if (!in_quote && !in_comment && (c == '\'' || c == '"')) {
			in_quote = 1;
			quote_type = c;
		}
		/* check to see if this is an escape sequence in a quote */
		if (in_quote && c == '\\' && !escape)
			escape = 1;
		else
			escape = OUT;

		/* if we are not in a comment then display the current char*/
		if (!in_comment)
			putchar(c);
	} // end while

	/*  after while loop we should not be in a comment, but we check anyway  */
	if (in_comment) {
        /* checks to see if incomplete comment  */
                 printf ("\nERROR: Incomplete comment at line %d \n", lineCounter);


	}
	return 0;
} // end de-comment
