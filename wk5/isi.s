# COMP1521 Practice Prac Exam #1
# main program + show function

   .data
msg1:
   .asciiz "The matrix\n"
msg2:
   .asciiz "is an identity matrix\n"
msg3:
   .asciiz "is not an identity matrix\n"
   .align  2

   .text
   .globl main
main:
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)

   la   $a0, m
   lw   $a1, N
   jal  is_ident      # s1 = is_ident(m,N)
   move $s1, $v0

   la   $a0, msg1
   li   $v0, 4
   syscall           # printf("The matrix\n")
   la   $a0, m
   lw   $a1, N
   jal  showMatrix   # showMatrix(m, N)

main_if:             # if (s1)
   beqz $s1, main_else
   la   $a0, msg2
   li   $v0, 4
   syscall           # printf("is an identity matrix\n")
   j    end_main_if

main_else:           # else
   la   $a0, msg3
   li   $v0, 4
   syscall           # printf("is not an identity matrix\n")

end_main_if:
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

# end main()

# void showMatrix(m, N)
# params: m=$a0, N=$a1
# locals: m=$s0, N=$s1, row=$s2, col=$s3
showMatrix:
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)

   move $s0, $a0
   move $s1, $a1
   li   $s2, 0
show_matrix_loop1:
   bge  $s2, $s1, end_show_matrix_loop1

   li   $s3, 0
show_matrix_loop2:
   bge  $s3, $s1, end_show_matrix_loop2

   li   $a0, ' '          # putchar(' ')
   li   $v0, 11
   syscall

   move $t0, $s2
   mul  $t0, $t0, $s1
   add  $t0, $t0, $s3
   li   $t1, 4
   mul  $t0, $t0, $t1
   add  $t0, $t0, $s0
   lw   $a0, ($t0)
   li   $v0, 1            # printf("%d",m[row][col])
   syscall

   addi $s3, $s3, 1       # col++
   j    show_matrix_loop2

end_show_matrix_loop2:
   li   $a0, '\n'         # putchar('\n')
   li   $v0, 11
   syscall

   addi $s2, $s2, 1       # row++
   j    show_matrix_loop1

end_show_matrix_loop1:

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

   .text
   .globl is_ident

# params: m=$a0, n=$a1
is_ident:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   # if you need to save more than four $s? registers
   # add extra code here to save them on the stack

# ... your code for the body of is_ident(m,N) goes here ...


   li    $s0, 0                  # initialise $s0 to be row = 0
   li    $s1, 0                  # initialise $s1 to be column = 0

while:
   lw    $t0, ($a0)
   beq   $s0, $s1, check_first     # if (row == col) then check_first

check_second:                       # if (m[row][col] != 0) return 0;
   beq   $t0, $0, column_while_end
   j     not_ident_matrix

check_first:                       # if (m[row][col] != 1) return 0;
   li    $t1, 1
   beq   $t1, $t0, column_while_end
   j     not_ident_matrix
   

column_while_end:
   addi  $a0, 4                  # increment pointer

   addi  $s1, $s1, 1             # increment col
   bge   $s1, $a1, row_while_end  # (col >= n) then increment row
   j     while              # else, loop again

row_while_end:
   li    $s1, 0                  # set col = 0
   addi  $s0, $s0, 1             # increment row
   bge   $s0, $a1, is_ident_matrix    # (row >= n) then done: return 1
   j  while                 # else, loop again

is_ident_matrix:                      # return $v0 = 1 which means true
   li    $v0, 1
   j     exit

not_ident_matrix:                     # return $v0 = 0 which means false
   li    $v0, 0


exit:

# epilogue
   # if you saved more than four $s? registers
   # add extra code here to restore them
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