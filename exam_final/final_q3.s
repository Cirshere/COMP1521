# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

main:
    li   $v0, 5
    syscall
    move $t0, $v0
    
    li $t1, 0xff
    li $t2, 0xff00
    
    and $t3, $t1, $t0
    and $t4, $t2, $t0
    
    srl $t4, $t4, 8
    
    bne $t3, $t4, not_equal
    
    li $v0, 1
    li $a0, 1
    syscall
    j end
    
not_equal:

    li $v0, 1
    li $a0, 0
    syscall

end: 
    li $v0, 11
    la $a0, '\n'
    syscall

    li   $v0, 0
    jr   $ra
