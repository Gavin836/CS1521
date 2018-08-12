#include <stdio.h>

int main (void) {
    
    
    unsigned int j = 31;
    unsigned int div = 1;
       
       while(j > 0) {
           div = div * 2;
           j--;
           printf("%d\n", div);
       } 
       
       
    return 0;
}
