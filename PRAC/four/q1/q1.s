# COMP1521 Practice Prac Exam #1
# int novowels(char *src, char *dest)

   .text
   .globl novowels

# params: src=$a0, dest=$a1
novowels:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)

   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)

   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...

   # add code for your novwels function here
   la   $a0, s1      #src 
   la   $a1, s2      #dest 

   li   $s0, 0       #i
   li   $s1, 0       #j
   li   $s3, 0       #n
   li   $s4, 0       #ch
# for (i = 0; src[i] != '\0';  i++)
while:
   li   $t1, 1
   add  $s4, $a0, $t1 
   beqz $s4, end_while
   move $v0, $t1
   jal isvowel

   beqz $v0, while_else
   addi $s3, $s3, 1
   j while_step

while_else:
   add  $t1, $a1, $s1
   sb   $s4, ($t1)
   addi $s1, $s1, 1

while_step:
   addi $s0, $s0, 1
   j while

end_while:
   add  $t1, $a1, $s1
   sb   $0, ($t1)






# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4

   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

#####

# auxiliary function
# int isvowel(char ch)
isvowel:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)

# function body
   li   $t0, 'a'
   beq  $a0, $t0, match
   li   $t0, 'A'
   beq  $a0, $t0, match
   li   $t0, 'e'
   beq  $a0, $t0, match
   li   $t0, 'E'
   beq  $a0, $t0, match
   li   $t0, 'i'
   beq  $a0, $t0, match
   li   $t0, 'I'
   beq  $a0, $t0, match
   li   $t0, 'o'
   beq  $a0, $t0, match
   li   $t0, 'O'
   beq  $a0, $t0, match
   li   $t0, 'u'
   beq  $a0, $t0, match
   li   $t0, 'U'
   beq  $a0, $t0, match

   li   $v0, 0
   j    end_isvowel
match:
   li   $v0, 1
end_isvowel:

# epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra
