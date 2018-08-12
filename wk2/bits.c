// COMP1521 18s1 Week 02 Lab (warm-up)

#include <stdio.h>
#include <math.h>

#define BYTE_SIZE 8




int main() {
	// Code to generate and display the largest "int" value
    int x = ~0;
    x = x ^ (1 << ((sizeof(int) * BYTE_SIZE) -1));    
    
	printf("int %x, %d\n", x, x);


	// Code to generate and display the largest "unsigned int" value

	unsigned int y = ~0;
	printf("unsigned int %x, %d\n", y, y);

	// Code to generate and display the largest "long int" value

	long int xx = 00;
	xx = ~xx;
	xx = xx ^ (sizeof(long) * BYTE_SIZE -1);
	printf("long int %x, %d\n", xx, xx);

	// Code to generate and display the largest "unsigned long int" value
/*
	unsigned long int xy = ??;
	printf("unsigned long int %x, %?\d", xy, xy);

	// Code to generate and display the largest "long long int" value

	long long int xxx = ??;
	printf("long long int %x, %d\n", xxx, xxx);

	// Code to generate and display the largest "unsigned long long int" value

	unsigned long long int xxy = ??;
	printf("unsigned long long int %x, %d\n", xxy, xxy);
*/
	return 0;
}

