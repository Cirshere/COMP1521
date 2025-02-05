# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

main:

    li $t0, 0          # i = 0;
    li $t1, 0          # sum = 0;
    
loop1:
    bge $t1, 42, loop1_end
    
    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t2, $v0      #   x
    
    la $t3, numbers
    mul $t4, $t0, 4
    add $t4, $t3, $t4
    
    sb $t2, ($t4)
    
    add $t1, $t1, $t2  # sum += x;
    addi $t0, $t0, 1   # i++;
    
    j loop1
loop1_end:

loop2:
    blez $t0, loop2_end
    sub $t0, $t0, 1    
    
    la $t3, numbers
    mul $t4, $t0, 4
    add $t4, $t3, $t4

    lb $t2, ($t4)

    move $a0, $t2
    li   $v0, 1
    syscall

    li   $a0, '\n'     
    li   $v0, 11
    syscall
    
    j loop2
loop2_end:

    li   $v0, 0        # return 0
    jr   $ra
    
    .data
    
numbers: .space 4000
    
