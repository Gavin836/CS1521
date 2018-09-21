#include <stdio.h>
#include <stdlib.h>

int main (void) {
	char ch;
	int i, j;
	j = 100;
	FILE *fp;
	
	fp = fopen("~/CS1521/Lectures/test.txt", "r");
		
		while (((ch = fgetc(fp)) != EOF) || (i < j)) {

			printf("%d", i);
			if (ch >= 'a' && ch <= 'z'){
				putchar(ch);
			}

			i++;
		}
	return 0;
}