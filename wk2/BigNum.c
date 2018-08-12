// BigNum.h ... LARGE positive integer values

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "BigNum.h"

#define YES 1
#define NO 0

// Initialise a BigNum to N bytes, all zeros.
void initBigNum(BigNum *n, int Nbytes)
{
   //n->bytes = calloc(Nbytes, sizeof(Byte));
   n->bytes = malloc(Nbytes * sizeof(Byte));
   memset(n->bytes, 0, Nbytes * sizeof(Byte));
   
   n->nbytes = Nbytes;
   
   assert(n->bytes != NULL);
   assert(n->nbytes != 0);
   
   return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum n, BigNum m, BigNum *res) 
{

     int i = 0;
     int n_value = 0;
     int m_value = 0;
     
     int carry_over = 0;
     int total = 0;
     
     int max_size = 0;
          
     while(i < n.nbytes || i < m.nbytes) {
        
        if (n.bytes[i] != 0 && i < n.nbytes) {
            n_value = n.bytes[i] - '0';
        }
        
        if (m.bytes[i] != 0 && i < m.nbytes) {
            m_value = m.bytes[i] - '0';
        }
        
        total = n_value + m_value + carry_over;
        
        //Reset
        carry_over = 0;
        n_value = 0;
        m_value = 0;
             
        //Determine if a 1 needs to be carried over   
        if (total > 9){
            total = total - 10;
            carry_over = 1;       
        }
        
        // Allocate memory as required
        if (i > res->nbytes) {
            res->bytes = realloc(res->bytes, abs(n.nbytes - m.nbytes));
            
            max_size = res->nbytes; 
            
            while (max_size < abs(n.nbytes - m.nbytes)) {
                res->bytes[max_size] = 0;
                max_size++;
            }
            
            res->nbytes = abs(n.nbytes - m.nbytes);
        }
        
        res->bytes[i] = total + '0';
        
         
        i++;
     }
   
   return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *n)
{

   int return_value = 0;
   int temp[30] = {0};
   //Byte *temp = calloc(n->bytes, sizeof(Bytes));
   int i = 0;
   int j = 0;
   
   //Adjust nbytes
   if (strlen(s) > n->nbytes) {
       n->nbytes = strlen(s);
       n->bytes = realloc(n->bytes, n->nbytes * sizeof(Byte));
       memset(n->bytes, 0, n->nbytes * sizeof(Byte));        
       
   }
   
   //Remove all non-number characters
   while (i < strlen(s)) {
        
        if (s[i] >= '0' && s[i] <= '9') {
            return_value = 1;
            temp[j] = s[i];
            j++;
        }
        
       i++;
   }
   
   //Remove zeros in front
   int first = 0;
   int zeroed = NO;
   
   while (first < j && zeroed == NO) {
        if (temp[first] == '0' ) {
            first ++;
        
        } else {
            zeroed = YES;
        }
   }
   
   
   //Reverse direction of string
   if (i != 0) {
        i = 0;
        j--;
        
        while (j >= first) {
            n->bytes[i] = temp[j];
            
            j--;
            i++;
        }
   
   }
   
   return return_value;
}

// Display a BigNum as string of characters
void showBigNum(BigNum n)
{

   int i = 0;   
   int first = -1;
   
   while (i < n.nbytes){
      
       if (n.bytes[i] != '0') {
            first = i;
       }
        
       i++;
   }   

   if (first == -1) {
        printf("0");
    
   } else  {
       
       while (first >= 0) {
           
           if (n.bytes[first] >= '0' && n.bytes[first] <= '9') { 
               printf("%c", n.bytes[first]);
           }
           first--;
       }
   }
   
   return;
}

