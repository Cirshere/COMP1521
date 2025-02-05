# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:

    # int i = 0;
    li $t0, 0
    
loop1: 
    bge $t0, 1000, loop1_end
    li $t3, 1
    la $t1, prime       # &prime
    
    mul $t2, $t0, 4     # i * 4
    add $t2, $t1, $t2   # &prime[i]
    sb $t3, ($t2)       # prime[i] = 1;

    addi $t0, $t0, 1
    b loop1
loop1_end:
    
    # i = 2
    li $t0, 2

loop2:
    bge $t0, 1000, loop2_end
    
    mul $t2, $t0, 4     # i * 4
    add $t2, $t1, $t2   # &prime[i]
    lb $t3, ($t2)       # t3 = prime[i]
    
    bne $t3, 1, not_one 
    
    # printf("%d", prime[i]);
    li $v0, 1       
    move $a0, $t0
    syscall
    
    li $v0, 11
    li $a0, '\n'
    syscall

    # int j = i * 2
    mul $t4, $t0, 2
    
loop3:
    bge $t4, 1000, loop3_end

    mul $t5, $t4, 4
    add $t5, $t1, $t5
    
    li $t6, 0
    sb $t6, ($t5)

    add $t4, $t4, $t0
    b loop3
loop3_end:

not_one:

    addi $t0, $t0, 1
    b loop2
loop2_end:

    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000
