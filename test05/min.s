#  print the minimum of two integers
main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bgt  $t0, $t1, if   #   if (x < y) {
    move $a0, $t0       #       printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'      #       printf("%c", '\n');
    li   $v0, 11
    syscall
                        #   } else {
    b end
if:
    move $a0, $t1       
    li   $v0, 1
    syscall
    
    li   $a0, '\n'
    li   $v0, 11
    syscall      
                        #   }    
end:

    li $v0, 0           # return 0
    jr $31
