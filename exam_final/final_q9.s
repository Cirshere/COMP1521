# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression

main:
    la   $a0, line
    la   $a1, 10000
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    la $t0, line
    lb $t1, ($t0)

    li   $v0, 0          # return 0
    jr   $31

expression:

term:

number:
    li $t0, 0

loop1:
    
    
loop1_end:


.data
line:
    .space 10000

