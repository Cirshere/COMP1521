main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0       #   t0 = x

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0       #   t1 = y

    add $t2, $t0, 1     #   i = x + 1;

loop1:
    bge $t2, $t1, end1    
    beq $t2, 13, else
    
    move $a0, $t2          #   printf("%d", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
else:    
    add $t2, $t2, 1
    b loop1
end1:

end:

    li $v0, 0           # return 0
    jr $31
