# read a line and print its length

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    la   $a0, str1       # printf("Line length: ");
    li   $v0, 4
    syscall

    li $t1, 0            # i = 0;

if_not_end:

    la $t2, line
    add $t3, $t2, $t1
    lb $t4, ($t3)
    
    addi $t1, $t1, 1
    bnez $t4, if_not_end
    
    sub $t1, $t1, 1
    
    move   $a0, $t1         # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256

