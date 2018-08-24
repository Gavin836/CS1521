// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

#define BYTES 8

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
   struct _bit_fields x = {14, 0, 0};
   //printf("%u\n",sizeof(x));      
   
   unsigned int  *pointer = (unsigned int *) &x;   
   //printf("%p\n", pointer);
  
   unsigned int mask = 1;
   
   int i = 0;
   
   while (i < sizeof(x) * BYTES) {
       int print = 0;
       
       if( (*pointer & mask) != 0){
            print = 1;
       } 
       
       printf("%d", print);
       
       
       i++;
       mask = mask << 1;
       print = 0;
   }
   
   printf("\n");
   
   
   return 0;
}
