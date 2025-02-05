########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by <<Christopher Hoang, z5259780>>, July 2020.


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE	=    1
MAX_WORLD_SIZE	=  128
MIN_GENERATIONS	= -256
MAX_GENERATIONS	=  256
MIN_RULE	=    0
MAX_RULE	=  255

# Characters used to print alive/dead cells.

ALIVE_CHAR	= '#'
DEAD_CHAR	= '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES	= (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

	.data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:	.space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:	    .asciiz "Enter world size: "
error_world_size:	    .asciiz "Invalid world size\n"
prompt_rule:		    .asciiz "Enter rule: "
error_rule:		        .asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

	.text

	#
	# $s0 - world_size
	# $s1 - rule
	# $s2 - n_generations
	# $s3 - reverse
	#
	# t0 - i, g | Changes
	# t1 - array manipulation | Changes
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#

main:
    
    # function prologue
    addi    $sp, $sp, -4
    sw      $ra, ($sp)
    
    # printf("Enter world size: ");
    la      $a0, prompt_world_size       
    li      $v0, 4
    syscall
    
    # scanf("%d", &world_size);    
    li      $v0, 5                       
    syscall
    move    $s0, $v0
    
    
    # if (world_size < MIN_WORLD_SIZE) {
    bge     $s0, MIN_WORLD_SIZE, not_invalid_size1
    
    #   printf("Invalid world size");
    la      $a0, error_world_size
    li      $v0, 4
    syscall
    b       end
    # }
    
not_invalid_size1:
    # if (world_size > MAX_WORLD_SIZE) {
    ble     $s0, MAX_WORLD_SIZE, not_invalid_size2

    #   printf("Invalid world size");
    la      $a0, error_world_size
    li      $v0, 4
    syscall    
    b       end
    # }
    
not_invalid_size2:    
    
    # printf("Enter rule: ");
    la      $a0, prompt_rule            
    li      $v0, 4
    syscall

    # scanf(%d, &rule);    
    li      $v0, 5                      
    syscall
    move    $s1, $v0                    
    
    # if (rule < MIN_RULE)
    bge     $s1, MIN_RULE, not_invalid_rule1
    
    #   printf ("Invalid rule\n");
    la      $a0, error_rule
    li      $v0, 4
    syscall
    b       end    
    

    # }
    
not_invalid_rule1:
    # if (rule > MAX_RULE) {
    ble     $s1, MAX_RULE, not_invalid_rule2
    
    #   printf ("Invalid rule\n");
    la      $a0, error_rule
    li      $v0, 4
    syscall
    b       end
    # }

not_invalid_rule2:

    # printf("Enter how many generations: ");
    la      $a0, prompt_n_generations
    li      $v0, 4
    syscall
    
    # scanf("%d", $n_generations);
    li      $v0, 5
    syscall
    move    $s2, $v0
    
    # if (generations < MIN_GENERATIONS) {
    bge     $s2, MIN_GENERATIONS, not_invalid_gen1
    
    # printf ("Invalid number of generations\n")
    la      $a0, error_n_generations
    li      $v0, 4
    syscall    
    b       end   
    # }

not_invalid_gen1:
    # if (generations > MAX_GENERATIONS) {
    ble     $s2, MAX_GENERATIONS, not_invalid_gen2

    # printf ("Invalid number of generations\n")
    la      $a0, error_n_generations
    li      $v0, 4
    syscall
    b       end  
    # }

not_invalid_gen2:

    # putchar('\n');    
    li      $a0, '\n'                   
    li      $v0, 11
    syscall
    
    # if (n_generations < 0) {
    bgtz    $s2, not_negative
    #   reverse = 1
    li      $s3, 1
    #   n_generations = -n_generations
    mul     $s2, $s2, -1
    
    b       else_negative
    # } 
    
    
not_negative:
    # reverse = 0
    li      $s3, 0    

else_negative: 

    #int i = 0;
    li      $t0, 0    
    # world_size - 1
    sub     $t2, $s0, 1


    # cells[0][world_size / 2] = 1;
    la      $t0, cells      # array address
    div     $t1, $s0, 2     # world_size / 2  also  column offset
    add     $t0, $t0, $t1   # address of cells[0][world_size/2]
    li      $t1, 1          # t1 = 1, temporary placeholder for 1
    sb      $t1, ($t0)      # array[0][world_size/2] = 1;
    
    #int g = 1;
    li      $t0, 1    
    
gen_loop:
    # while (g <= n_generations)
    bgt     $t0, $s2, gen_loop_end
    
    move    $a0, $s0    # world_size
    move    $a1, $t0    # g
    move    $a2, $s1    # rule
    jal     run_generation

    # g++:
    addi    $t0, $t0, 1
    
    b gen_loop
gen_loop_end:

    
    beqz    $s3, else_print
    # g = n_generations
    move    $t0, $s2 

if_reverse_loop:
    bltz    $t0, if_reverse_loop_end
    
    move    $a0, $s0       # world_size
    move    $a1, $t0       # g
    jal     print_generation 
    
    sub     $t0, $t0, 1
    b       if_reverse_loop
if_reverse_loop_end:
    b       end

else_print:

    # g = 0
    li      $t0, 0
positive_print_loop:
    bgt     $t0, $s2, positive_print_loop_end

    move    $a0, $s0        # world_size
    move    $a1, $t0        # g
    jal print_generation

    addi    $t0, $t0, 1
    b       positive_print_loop
positive_print_loop_end:     

end:    

    #function epilogue
    lw      $ra, ($sp)
    addi    $sp, $sp, 4

    li	$v0, 0
    jr	$ra

    

	#
	# Given `world_size', `which_generation', and `rule', calculate
	# a new generation according to `rule' and store it in `cells'.
	#

	#
	# $t1 - x | Changes 
	# $t2 - left | Changes
	# $t3 - center | Changes
	# $t4 - right | Changes
	# $t5 - world_size
	# $t6 - which generation
	# $t7 - rule
	# $t7 - $t9 used for address calculation
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `run_generation' FINISHES
	#
	
	

run_generation:

    #function prologue
    addi    $sp, $sp, -4
    sw      $ra, ($sp)


    # int x = 0;
    li      $t1, 0
    move    $t5, $s0    # t5 = world_size
    move    $t6, $t0    # t6 = which_generation 
 
run_gen_loop:
    bge     $t1, $s0, run_gen_loop_end
    
    # int left = 0;
    li      $t2, 0
    
    # if (x > 0) {
    beqz    $t1, x_zero
    
    # left = cells[which_generation - 1][x - 1];
    la      $t7, cells      # t7 = &cells
    sub     $t8, $t6, 1     # t8 = which_generation - 1;
    mul     $t8, $t8, $t5   # t8 = row offset
    sub     $t9, $t1, 1     # t9 = x - 1 = column offset
    add     $t8, $t8, $t9   # t8 = row + col offset
    add     $t7, $t7, $t8   # t7 = &cells[which_generation - 1][x - 1];
    lb      $t2, ($t7)      # left = cells[which_generation - 1][x - 1];
    
    # }
x_zero:    

    #int center = cells[which_generation - 1][x];
    la      $t7, cells      # t7 = &cells
    sub     $t8, $t6, 1     # t8 = which_generation - 1;
    mul     $t8, $t8, $t5   # t8 = row offset 
    add     $t9, $t8, $t1   # t9 = row + col offset
    add     $t7, $t7, $t9   # t7 = &cells[which_generation - 1][x];
    lb      $t3, ($t7)      # center = cells[which_generation - 1][x];
    
    # int right = 0;
    li      $t4, 0
    # world_size - 1;
    sub     $t5, $t5, 1
    
    # if(x < world_size - 1) {
    bge     $t1, $t5, x_world_size_1
    
    # right = cells[which_generation - 1][x + 1];
    la      $t7, cells          # t7 = &cells 
    addi    $t9, $t1, 1         # x + 1; col offset
    add     $t9, $t8, $t9       # t9 = col + row offset
    add     $t7, $t7, $t9       # t7 = &cells[which_generation - 1][x + 1];
    lb      $t4, ($t7)          # right = cells[which_generation - 1][x + 1];
        
    # }
    
x_world_size_1:    

    # int state = left << 2 | center << 1 | right << 0
    
    # left << 2
    sll     $t2, $t2, 2
    # center << 1
    sll     $t3, $t3, 1
    # left << 0
    sll     $t4, $t4, 0 
    
    # $t2 = state
    # t2 = left | center
    or      $t2, $t2, $t3
    
    # state = (left | center) | right
    or      $t2, $t2, $t4
    
    li      $t4, 1
    
    # $t3 = bit
    # int bit = 1 << state
    sllv    $t3, $t4, $t2
    
    # $t7 = rule    
    move    $t7, $s1
    
    # $t4 = set
    # int set = rule & bit
    and     $t4, $t3, $t7

    # t5 = world_size
    move    $t5, $s0
    
    la      $t9, cells      # &cells
    mul     $t8, $t6, $t5   # column offset
    add     $t8, $t8, $t1   # column + row offset
    add     $t9, $t9, $t8   # &cells[which_generation][x]

    # if (set) {
    beqz    $t4, not_one
    # cells[which_generation][x] = 1;
    li      $t3, 1
    sb      $t3, ($t9)
    
    b if_end
    # }
not_one:
    # cells[which_generation][x] = 0;
    li      $t3, 0
    sb      $t3, ($t9)    

if_end:        
    
    # x++;
    addi    $t1, $t1, 1    
    b       run_gen_loop
run_gen_loop_end:

    # function epilogue
    lw      $ra, ($sp)
    addi    $sp, $sp, 4

	jr	    $ra


	#
	# Given `world_size', and `which_generation', print out the
	# specified generation.
	#
    # t1 = x | Change values
	# t2 = world_size
	# t3 = g
	# t4 - t6 = address calculation | Changes values 
	# t7 = cells[which_generation][x] | Changes values
	# 
	#
	# YOU SHOULD ALSO NOTE WHICH REGISTERS DO NOT HAVE THEIR
	# ORIGINAL VALUE WHEN `print_generation' FINISHES
	#

print_generation:

    #function prologue
    addi    $sp, $sp, -4
    sw      $ra, ($sp)

    # int x = 0;
    li      $t1, 0
    
    move    $t2, $a0 # world_size
    move    $t3, $a1 # g
    
    # printf("%d", which_generation);
    li      $v0, 1
    move    $a0, $t3
    syscall
    
    #putchar ('\t');
    li      $v0, 11
    li      $a0, '\t'
    syscall
    
print_generation_loop:
    bge     $t1, $t2, print_generation_loop_end
    
    la      $t4, cells      # &cells
    mul     $t5, $t3, $t2   # col offset
    add     $t5, $t5, $t1   # col + row offset
    add     $t6, $t5, $t4   # &cells[which_generation][x]

    lb      $t7, ($t6)      # t7 = cells[which_generation][x]

    beqz    $t7, if_dead
    
    li      $v0, 11
    li      $a0, ALIVE_CHAR
    syscall
    
    b if_alive_end    
if_dead:
    
    li      $v0, 11
    li      $a0, DEAD_CHAR
    syscall

if_alive_end:    

    add $t1, $t1, 1
    b print_generation_loop
print_generation_loop_end:    

    li      $v0, 11
    li      $a0, '\n'
    syscall
    
    #function epilogue
    
    lw $ra, ($sp)
    addi $sp, $sp, 4

	jr	$ra
