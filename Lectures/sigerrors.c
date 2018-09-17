#include <stdio.h>
#include <stdlib.h>

int main (void) {
	int j = 0;
	int *x = &j;
	*x = 'a';

	printf("%d %d", j, *x);
	return 0;
}