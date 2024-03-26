# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li $t0, 0            # int i = 0;
    
if_not_end:
    la $t1, line
    add $t1, $t0, $t1
    lb $t2, ($t1)
    
    addi $t0, $t0, 1
    bnez $t2, if_not_end
    
    sub $t0, $t0, 1
    
    li $t3, 0            # int j = 0;
    sub $t4, $t0, 2      # int k = i - 2;
    
loop1:
    bge $t3, $t4, loop_end1
    
    la $t1, line
    
    add $t5, $t1, $t3    # &line[j]
    add $t6, $t1, $t4    # &line[k]
    lb $t5, ($t5)        # line[j]
    lb $t6, ($t6)        # line[k]
    
    beq $t5, $t6, pal
    
    la   $a0, not_palindrome
    li   $v0, 4
    syscall   
    j end 

pal:

    addi $t3, $t3, 1
    sub $t4, $t4, 1
    
    
    b loop1
loop_end1:

    la   $a0, palindrome
    li   $v0, 4
    syscall
 
end:
    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

