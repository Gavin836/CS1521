############################################################ -*- asm -*-
# COMP1521 18s2 -- Assignment 1 -- Scrolling Text!
# Scroll letters from a message in argv[1]
#
# Base code by Jashank Jeremy
# Tweaked by John Shepherd
# $Revision: 1.5 $
#
# Edit me with 8-column tabs!

# Requires:
#  - `all_chars', defined in chars.s

# Provides:
	.globl	main # :: int, [char *], [char *] -> int
	.globl	setUpDisplay # :: int, int -> void
	.globl	showDisplay # :: void -> void
	.globl	delay # :: int -> vovid
	.globl	isUpper # :: char -> int
	.globl	isLower # :: char -> int

	.globl	CHRSIZE
	.globl	NROWS
	.globl	NDCOLS
	.globl	MAXCHARS
	.globl	NSCOLS
	.globl	CLEAR


########################################################################
	.data

	# /!\ NOTE /!\
	# In C, the values of the symbols `CHRSIZE', `NROWS', `NDCOLS',
	# `NSCOLS', `MAXCHARS', and `CLEAR' would be substituted during
	# preprocessing.  SPIM does not have preprocessing facilities,
	# so instead we provide these values in the `.data' segment.

	# # of rows and columns in each big char
CHRSIZE:	.word	9
	# number of rows in all matrices
NROWS:		.word	9
	# number of columns in display matrix
NDCOLS:		.word	80
	# max length of input string
MAXCHARS:	.word	100
	# number of columns in bigString matrix
	# max length of buffer to hold big version
	# the +1 allows for one blank column between letters
NSCOLS:		.word	9000	# (NROWS * MAXCHARS * (CHRSIZE + 1))
        # ANSI escape sequence for 'clear-screen'
CLEAR:	.asciiz "\033[H\033[2J"
# CLEAR:	.asciiz "__showpage__\n" # for debugging

main__0:	.asciiz	"Usage: ./scroll String\n"
main__1:	.asciiz	"Only letters and spaces are allowed in the string!\n"
main__2:	.asciiz "String mush be < "
main__3:	.asciiz " chars\n"
main__4:	.asciiz "Please enter a string with at least one character!\n"

	.align	4
theString:	.space	101	# MAXCHARS + 1
	.align	4
display:	.space	720	# NROWS * NDCOLS
	.align	4
bigString:	.space	81000	# NROWS * NSCOLS


########################################################################
# .TEXT <main>
	.text
main:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
# Uses:		$a0, $a1, $t0, $t1, $t2, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
# Clobbers:	...

# Locals:
#	- `theLength' in $s0
#	- `bigLength' in $s1
#	- `i' in $s2
#	- `ch' in $s3
#	- `str' in $t2
#	- `row' in $s4
#	- `col' in $s5
#	- `iterations' in $s6
#	- `startingCol' in $s7

# Structure:
#	main
#	-> [prologue]
#	-> main_argc_gt_two
#	-> main_PTRs_init
#	  -> main_PTRs_cond
#	    -> main_ch_notspace
#	    -> main_ch_isLower
#	    -> main_ch_isSpace
#	  -> main_PTRs_step
#	-> main_PTRs_f
#	[theLength cond]
#	  | main_theLength_ge_MAXCHARS
#	  | main_theLength_lt_MAXCHARS
#	  | main_theLength_lt_1
#	  | main_theLength_ge_1
#	...
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	$fp, -4($sp)
	la	$fp, -4($sp)
	sw	$ra, -4($fp)  # note: switch to $fp-relative
	sw	$s0, -8($fp)
	sw	$s1, -12($fp)
	sw	$s2, -16($fp)
	sw  $s3, -20($fp)
	sw  $s4, -24($fp)
	sw  $s5, -28($fp)
    sw  $s6, -32($fp)
    sw  $s7, -36($fp)
	addi	$sp, $sp, -40

	# if (argc < 2)
	li	$t0, 2
	bge	$a0, $t0, main_argc_gt_two
	nop	# in delay slot
	# printf(...)
	la	$a0, main__0
	li	$v0, 4 # PRINT_STRING_SYSCALL
	syscall
	# return 1  =>  load $v0, jump to epilogue
	li	$v0, 1
	j	main__post
	nop	# in delay slot
main_argc_gt_two:

	move	$s0, $zero
main_PTRs_init:
	# s = argv[1]
	lw	$t2, 4($a1)
main_PTRs_cond:
	# optimisation: `ch = *s' now
	# (ch = )*s
	lb	$s2, ($t2)
	# *s != '\0'  =>  ch != 0
	beqz	$s2, main_PTRs_f
	nop	# in delay slot

	# if (!isUpper(ch))
main_ch_upper:
	move	$a0, $s2
	jal	isUpper
	nop	# in delay slot
	beqz	$v0, main_ch_lower
	nop	# in delay slot
	j	main_ch_ok
	nop	# in delay slot
	# if (!isLower(ch))
main_ch_lower:
	move	$a0, $s2
	jal	isLower
	nop	# in delay slot
	beqz	$v0, main_ch_space
	nop	# in delay slot
	j	main_ch_ok
	nop	# in delay slot
	# if (ch != ' ')
main_ch_space:
	li	$t0, ' '
	bne	$s2, $t0, main_ch_fail
	nop	# in delay slot
	j	main_ch_ok
	nop	# in delay slot

main_ch_fail:
	# printf(...)
	la	$a0, main__1
	li	$v0, 4 # PRINT_STRING_SYSCALL
	syscall
	# exit(1)  =>  return 1  =>  load $v0, jump to epilogue
	li	$v0, 1
	j	main__post
	nop	# in delay slot

main_ch_ok:
	# if (theLength >= MAXCHARS)
	la	$t0, MAXCHARS
	lw	$t0, ($t0)
	# break  =>  jump out of for(*s...)
	bge	$s0, $t0, main_PTRs_f

	# theString[theLength]
	la	$t0, theString
	addu	$t0, $t0, $s0	# ADDU because address
	# theString[theLength] = ch
	sb	$s2, ($t0)

	# theLength++
	addi	$s0, $s0, 1

main_PTRs_step:
	# s++  =>  s = s + 1
	addiu	$t2, $t2, 1	# ADDIU because address
	j	main_PTRs_cond
	nop
main_PTRs_f:

	# theString[theLength] = ...
	la	$t0, theString
	addu	$t0, $t0, $s0	# ADDU because address
	# theString[theLength] = '\0'
	sb	$zero, ($t0)

	# CHRSIZE + 1
	la	$t0, CHRSIZE
	lw	$t0, ($t0)
	addi	$t0, $t0, 1
	# bigLength = theLength * (CHRSIZE + 1)
	mul	$s1, $t0, $s0

	# if (theLength >= MAXCHARS)
	la	$t0, MAXCHARS
	lw	$t0, ($t0)
	blt	$s0, $t0, main_theLength_lt_MAXCHARS
	nop	# in delay slot

main_theLength_ge_MAXCHARS:
	# printf(..., ..., ...)
	la	$a0, main__2
	li	$v0, 4 # PRINT_STRING_SYSCALL
	syscall
	move	$a0, $t0
	li	$v0, 1 # PRINT_INT_SYSCALL
	syscall
	la	$a0, main__3
	li	$v0, 4 # PRINT_STRING_SYSCALL
	syscall
	# return 1  =>  load $v0, jump to epilogue
	li	$v0, 1
	j	main__post
	nop	# in delay slot
main_theLength_lt_MAXCHARS:

	# if (theLength < 1)
	li	$t0, 1
	bge	$s0, $t0, main_theLength_ge_1
	nop	# in delay slot

main_theLength_lt_1:
	# printf(...)
	la	$a0, main__4
	li	$v0, 4 # PRINT_STRING_SYSCALL
	syscall
	# exit(1)  =>  return 1  =>  load $v0, jump to epilogue
	li	$v0, 1
	j	main__post
	nop	# in delay slot
main_theLength_ge_1:

######################################################################

	# ... TODO ...
# initialise the display to all spaces

# Common registers:
#           - $s0: rows
#           - $s1: col
#			- s2: i
#			- t1: j

    li      $s2, 0            

main_init_spaces_row:
	la      $t7, NROWS
	lw 		$t7, ($t7)
	bge     $s2, $t7, main_init_spaces_row_end
	nop
	li      $t1, 0                      

main_init_spaces_col:
	la      $t2, NDCOLS
	lw 		$t2, ($t2)
	bge     $t1, $t2, main_init_spaces_col_end
	nop

	#display[i][j] = i * NDCOLS + j
	mul     $t2, $t2, $s2
	add     $t2, $t2, $t1
	la      $t3, display
	add     $t2, $t2, $t3
	
	li      $t3, ' '
	sb      $t3, ($t2)

main_init_spaces_skip:
	addi    $t1, $t1, 1
	j       main_init_spaces_col
	nop

main_init_spaces_col_end:
	addi    $s2, $s2, 1
	j       main_init_spaces_row
	nop

main_init_spaces_row_end:
#####################################################################
# Bigchars array

# Common Registers:
#					-s2: i counter
#					-t1: j counter 
#					-s4: rows
#					-s5: cols

	li $s2, 0                        

main_create_big:
	bge     $s2, $s0, main_create_bigend
	nop
	li      $s4, 0
	li      $s5, 0
	
	#ch = theString[i]
	la      $t2, theString
	add     $t2, $t2, $s2
	lb      $s3, ($t2)

	#Determine which hash matrix to store
		#if space
	li      $t2, ' '
	beq     $s3, $t2, main_create_big_spaces
	nop
	
		#if uppercase
	move    $a0, $s3
	jal     isUpper
	nop
	bne     $v0, $zero, main_create_upper
	nop

		#if lowercase
	move    $a0, $s3	
	jal     isLower
	nop
	bne     $v0, $zero, main_create_lower
	nop

main_create_upper:
    # which = ch - 'A'
    li      $t3, 'A'
	sub     $s3, $s3, $t3
	j       main_create_letter

main_create_lower:
    # which = ch - 'a' + 26
    li      $t3, 'a'
	sub     $t2, $s3, $t3
	addi    $s3, $t2, 26

main_create_letter:
	la      $t3, CHRSIZE
	lw 		$t3, ($t3)
	bge     $s4, $t3, main_create_gen_end
	move    $s5, $zero
	

main_create_letter_loop:
    la      $t3, CHRSIZE
	lw 		$t3, ($t3)
	bge     $s5, $t3, main_create_letter_loop_end

	#Calculate offset in bigString = row * NSCOLS + col + i * (CHRSIZE+1)
	addi    $t3, $t3, 1
	mul     $t3, $t3, $s2
	add     $t3, $t3, $s5
	la      $t4, NSCOLS
	lw 		$t4, ($t4)
	mul     $t4, $t4, $s4
	add     $t3, $t3, $t4
	la      $t4, bigString
	add     $t3, $t3, $t4
	
	# Offset in all_chars = which * CHRSIZE^2 + row * CHRSIZE + col
	la      $t7, CHRSIZE
	lw 		$t7, ($t7)
	mul     $t4, $s4, $t7
	add     $t4, $t4, $s5
	mul     $t7, $t7, $t7
	mul     $t2, $s3, $t7

	add     $t2, $t2, $t4
	la      $t4, all_chars
	add     $t2, $t2, $t4
	lb      $t2, ($t2)

	sb      $t2, ($t3)

main_create_letter_loop_step:
	addi    $s5, $s5, 1
	j       main_create_letter_loop

main_create_letter_loop_end:
	addi    $s4, $s4, 1
	j       main_create_letter

main_create_big_spaces:
	la      $t2, CHRSIZE
	lw 		$t2, ($t2)
	bge     $s4, $t2, main_create_gen_end
	nop
	li      $s5, 0 

main_create_big_spaces_loop:
	la      $t2, CHRSIZE
	lw 		$t2, ($t2)
	bge     $s5, $t2, main_create_big_spaces_loopend
	nop

	#Calculate offset in bigString = row * NSCOLS + col + i * (CHRSIZE+1)
	addi    $t2, $t2, 1
	mul     $t2, $t2, $s2
	add     $t2, $t2, $s5
	la      $t3, NSCOLS
	lw 		$t3, ($t3)
	mul     $t3, $t3, $s4
	add     $t2, $t2, $t3

	#Set the index position to space char
	la      $t4, bigString
	add     $t2, $t2, $t4
	li      $t3, ' '
	sb      $t3, ($t2)

main_create_big_spaces_step:
	addi    $s5, $s5, 1
	j       main_create_big_spaces_loop
	nop

main_create_big_spaces_loopend:
	addi    $s4, $s4, 1
	j       main_create_big_spaces
	nop

main_create_gen_end:
    # col = (i * (CHRSIZE+1)) + CHRSIZE
	la      $t7, CHRSIZE
	lw 		$t7, ($t7)
	addi    $t2, $t7, 1
	mul     $t2, $t2, $s2
	add     $t2, $t2, $t7
	move    $s5, $t2
	li      $s4, 0

main_create_gen_end_loop:
	bge     $s4, $t7, main_create_gen_end_loop_end

	# Calculate offset of bigString = row * NSCOLS + col
	la      $t2, NSCOLS
	lw 		$t2, ($t2)
	mul     $t2, $t2, $s4
	add     $t2, $t2, $s5
	la      $t3, bigString
	add     $t2, $t2, $t3
	li      $t3, ' '
	sb      $t3, ($t2)

	addi    $s4, $s4, 1
	j       main_create_gen_end_loop

main_create_gen_end_loop_end:
	addi    $s2, $s2, 1
	j       main_create_big 

main_create_bigend:

#####################################################################
#INTERATIONS
#Common registers:
#                   - $s2: i
#					- $s6: iterations
#					- $s7: starting_col

    # iterations = NDCOLS+bigLength
	la      $t7, NDCOLS
	lw 		$t7, ($t7)
	add     $s6, $s1, $t7
	# starting_col = NDCOLS-1
	sub     $s7, $t7, 1

	li      $s2, 0

main_interations_start:
	bge     $s2, $s6, main_interations_end
	nop
	move    $a0, $s7
	move    $a1, $s1
	jal     setUpDisplay	
	nop

	jal     showDisplay
	nop
	
	sub     $s7, $s7, 1
	li      $a0, 1
	#jal     delay
	nop

	addi    $s2, $s2, 1
	j       main_interations_start
	nop

main_interations_end:

    move    $v0, $zero

########################################################################

main__post:
	# tear down stack frame
	lw      $s7, -36($fp)
	lw      $s6, -32($fp)
	lw      $s5, -28($fp)
	lw      $s4, -24($fp)
	lw      $s3, -20($fp)
	lw	    $s2, -16($fp)
	lw	    $s1, -12($fp)
	lw	    $s0, -8($fp)
	lw	    $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	    # in delay slot


# .TEXT <setUpDisplay>
	.text
setUpDisplay:

# Frame:	$fp, $ra, $s0, $s1, $s2, $s3
# Uses:		$a0, $a1, $s0, $s1, $s2, $s3
# Clobbers:	...

# Locals:
#	- `row' in $s0
#	- `out_col' in $s1
#	- `in_col' in $s2
#	- `first_col' in $s3
#	- 'starting' in $a0
#	- 'length' in $a1

# Structure:
#	setUpDisplay
#	-> [prologue]
#	-> starting_condition1
#	-> starting_condition2
#	-> display_copy_main
#   -> display_copy_main_break
#	-> display_copy_mainend
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	    $fp, -4($sp)
	la	    $fp, -4($sp)
	sw	    $ra, -4($fp)
	sw 	    $s0, -8($fp)
	sw 	    $s1, -12($fp)
	sw  	$s2, -16($fp)
	sw 	    $s3, -20($fp)
	addi	$sp, $sp, -24

	# ... TODO ...
	# If starting < 0
	li      $s1, 0

	bge     $a0, $zero, setUpDisplay_else
	li      $s1, 0
	move    $s3, $a0
	li      $t0, -1
	mul     $s3, $s3, $t0
    j       setupUpDisplay_bigstring_bridge
    nop
    
setUpDisplay_else:
    move    $s3, $a0
	bge     $s1, $s3, setUpDisplay_space_else_end 
	nop         
	li      $s0, 0

setUpDisplay_space_row_loop:
	la      $t0, NROWS
	lw 		$t0, ($t0)
	bge     $s0, $t0, setUpDisplay_space_row_loop_end
	nop

	#Calculate the offset display[row][col] = ROWS * NROWS + OUTCOLS 
	mul     $t0, $t0, $s0
	add     $t0, $t0, $s1
	la      $t1, display

	add     $t0, $t0, $t1
	li      $t1, ' '
	sb      $t1, ($t0)

setUpDisplay_space_row_loop_step:
	addi    $s0, 1
	j       setUpDisplay_space_row_loop
	nop

setUpDisplay_space_row_loop_end:
	addi    $s1, 1
	j       setUpDisplay_else
	nop

setUpDisplay_space_else_end:
	li      $s3, 0

setupUpDisplay_bigstring_bridge:
    # in_col = first_col
    move    $s2, $s3

#Copy bigString into display
setUpDisplay_bigstring: 
	bge     $s2, $a1, setUpDisplay_bigstring_end
	nop
	
	la      $t1, NDCOLS
	lw 		$t1, ($t1)
	bge     $s1, $t1, setUpDisplay_bigstring_end
	li      $s0, 0

setUpDisplay_bigstring_row:
	la      $t0, NROWS 
	lw 		$t0, ($t0)
	bge     $s0, $t0, setUpDisplay_bigstring_row_end
	nop

#Calculate offset in bigString = row*NSCOLS + in_col
	la      $t0, NSCOLS
	lw 		$t0, ($t0)
	mul     $t7, $t0, $s0
	add     $t7, $t7, $s2
	la      $t1, bigString
	add     $t7, $t7, $t1
	lb      $t7, ($t7)

#Calculate offset in display = row*NDCOLS + out_col
	la      $t0, NDCOLS
	lw 		$t0, ($t0)
	mul     $t6, $t0, $s0
	add     $t6, $t6, $s1
	la      $t1, display
	add     $t6, $t6, $t1
	sb      $t7, ($t6)

setUpDisplay_bigstring_row_step:
	addi    $s0, $s0, 1
	j       setUpDisplay_bigstring_row
	nop

setUpDisplay_bigstring_row_end:
    #increment out_col and in_col
	addi    $s1, $s1, 1
	addi    $s2, $s2, 1

	j   setUpDisplay_bigstring
	nop

setUpDisplay_bigstring_end:

	# tear down stack frame
	lw      $s3, -20($fp)
	lw	    $s2, -16($fp)
	lw	    $s1, -12($fp)
	lw	    $s0, -8($fp)
	lw	    $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	    # in delay slot

########################################################################
# .TEXT <showDisplay>
	.text
showDisplay:

# Frame:	$fp, $ra, $s0, $s1, $s2
# Uses:		$s0, $s1, $s2
# Clobbers:	...

# Locals:
#	- `i' in $s0
#	- `j' in $s1
#	- 'row' in $s2

# Structure:
#	showDisplay
#	-> [prologue]
#	-> showDisplay_rows
#		-> showDisplay_cols
#		-> showDisplay_cols_end
#		-> showDisplay_cols_step
#	-> showDIsplay_rows_end
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	    $fp, -4($sp)
	la	    $fp, -4($sp)
	sw	    $ra, -4($fp)
	sw  	$s0, -8($fp)
	sw 	    $s1, -12($fp)
	addi    $sp, $sp, -16

	la	    $a0, CLEAR
	li	    $v0, 4 
	syscall

	li      $s0, 0
showDisplay_rows:
	la      $t1, NROWS
	lw 		$t1, ($t1)
	bge     $s0, $t1, showDisplay_rows_end
	li      $s1, 0

showDisplay_cols:
	lw      $t0, NDCOLS
	bge     $s1, $t0, showDisplay_cols_end

	#calculate offset display[i][j] = i * NDCOLS + j
	mul     $t0, $t0, $s0
	add     $t0, $t0, $s1
	la      $t1, display
	add     $t0, $t1, $t0
	lb      $a0, ($t0)
	li      $v0, 11
	syscall

showDisplay_cols_step:
	addi    $s1, $s1, 1
	j       showDisplay_cols
	nop

showDisplay_cols_end:
	addi    $s0, $s0, 1
	li      $a0, '\n'
	li      $v0, 11
	syscall

	j showDisplay_rows
	nop

showDisplay_rows_end:
	# tear down stack frame
	lw	    $s1, -12($fp)
	lw	    $s0, -8($fp)
	lw	    $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	# in delay slot

########################################################################
# .TEXT <delay>
	.text
delay:

# Frame:	$fp, $ra
# Uses:		$a0, $t0, $t1, $t2, $t3, $t4, $t5
# Clobbers:	$t0, $t1, $t2, $t3, $t4, $t5

# Locals:
#	- `n' in $a0
#	- `x' in $t0
#	- `i' in $t1
#	- `j' in $t2
#	- `k' in $t3

# Structure:
#	delay
#	-> [prologue]
#	-> delay_i_init
#	-> delay_i_cond
#	   -> delay_j_init
#	   -> delay_j_cond
#	      -> delay_k_init
#	      -> delay_k_cond
#	         -> delay_k_step
#	      -> delay_k_f
#	      -> delay_j_step
#	   -> delay_j_f
#	   -> delay_i_step
#	-> delay_i_f
#	-> [epilogue]

# Code:
	sw	    $fp, -4($sp)
	la	    $fp, -4($sp)
	sw	    $ra, -4($fp)
	la	    $sp, -8($fp)

	# x <- 0
	move	$t0, $zero
	# These values control the busy-wait.
	li	    $t4, 20000
	li	    $t5, 1000

delay_i_init:
	# i = 0;
	move	$t1, $zero
delay_i_cond:
	# i < n;
	bge	    $t1, $a0, delay_i_f
	nop	    # in delay slot

delay_j_init:
	# j = 0;
	move	$t2, $zero
delay_j_cond:
	# j < DELAY_J;
	bge	    $t2, $t4, delay_j_f
	nop	    # in delay slot

delay_k_init:
	# k = 0;
	move	$t3, $zero
delay_k_cond:
	# k < DELAY_K;
	bge	    $t3, $t5, delay_k_f
	nop	    # in delay slot

	# x = x + 1
	addi	$t0, $t0, 1

delay_k_step:
	# k = k + 1
	addi	$t3, $t3, 1
	j	    delay_k_cond
	nop	    # in delay slot
delay_k_f:

delay_j_step:
	# j = j + 1
	addi	$t2, $t2, 1
	j	    delay_j_cond
	nop	    # in delay slot
delay_j_f:

delay_i_step:
	# i = i + 1
	addi	$t1, $t1, 1
	j	    delay_i_cond
	nop	    # in delay slot
delay_i_f:

delay__post:
	# tear down stack frame
	lw	    $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	    # in delay slot

########################################################################
# .TEXT <isUpper>
	.text
isUpper:

# Frame:	$fp, $ra
# Uses:		$a0, ...
# Clobbers:	$v0, ...

# Locals:
#	- ...

# Structure:
#	isUpper
#	-> [prologue]
#	-> [epilogue]

# Code:
	
	# ... TODO ...
    # set up stack frame
	sw	    $fp, -4($sp)
	la	    $fp, -4($sp)
	sw	    $ra, -4($fp)
	la	    $sp, -8($fp)

	# if (ch >= 'A')
	li	    $v0, 'A'
	blt	    $a0, $v0, isUpper_ch_lt_a
	nop	    # in delay slot
isUpper_ch_ge_a:
	# if (ch <= 'Z')
	li	    $v0, 'Z'
	bgt	    $a0, $v0, isUpper_ch_gt_z
	nop	    # in delay slot
isUpper_ch_le_z:
	li	$v0, 1
	j	    isUpper_ch_phi
	nop	    # in delay slot

	# ... else
isUpper_ch_lt_a:

isUpper_ch_gt_z:
	move	$v0, $zero
	# fallthrough

isUpper_ch_phi:

isUpper__post:
	# tear down stack frame
	lw      $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	    # in delay slot
########################################################################
# .TEXT <isLower>
	.text
isLower:

# Frame:	$fp, $ra
# Uses:		$a0
# Clobbers:	$v0

# Locals:
#	- `ch' in $a0
#	- ... $v0 used as temporary register

# Structure:
#	isLower
#	-> [prologue]
#	[ch cond]
#	   | isLower_ch_ge_a
#	   | isLower_ch_le_z
#	   | isLower_ch_lt_a
#	   | isLower_ch_gt_z
#	-> isLower_ch_phi
#	-> [epilogue]

# Code:
	# set up stack frame
	sw	    $fp, -4($sp)
	la	    $fp, -4($sp)
	sw	    $ra, -4($fp)
	la	    $sp, -8($fp)

	# if (ch >= 'a')
	li	    $v0, 'a'
	blt	    $a0, $v0, isLower_ch_lt_a
	nop	    # in delay slot

isLower_ch_ge_a:
	# if (ch <= 'z')
	li	    $v0, 'z'
	bgt	    $a0, $v0, isLower_ch_gt_z
	nop	    # in delay slot

isLower_ch_le_z:
	li      $v0, 1
	j	    isLower_ch_phi
	nop	    # in delay slot

	# ... else
isLower_ch_lt_a:

isLower_ch_gt_z:
	move	$v0, $zero

	# fallthrough
isLower_ch_phi:

isLower__post:
	# tear down stack frame
	lw	    $ra, -4($fp)
	la	    $sp, 4($fp)
	lw	    $fp, ($fp)
	jr	    $ra
	nop	    # in delay slot

#################################################################### EOF
