// Copy input to output
// COMP1521 18s1

#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    
    if (argc == 1) { 
	    copy(stdin,stdout);
	
	} else {
	    FILE *f = fopen(argv[1], "r");
	    
	    if (f == NULL) {
	        printf("Can't read NameOfFile");
	    
	    } else {
	        copy(f, stdout);
	        fclose(f);
	    }
	    
	}
	
	
	
	
	return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode

void copy(FILE *input, FILE *output){

    char ch[SIZE] = {0};

    while(fgets(ch, SIZE, input) != NULL) {
        fputs(ch, output);

    }

}
