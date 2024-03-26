# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:

    li $t0, 0           # i = 1;
    li $t6, 0           # swapped = 0; - return value
loop1:
    bge $t0, 10, end1   # while (i < 10) {
    
    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $t4, ($t3)       #   loads numbers[i] into t4 'x'
    
    sub $t7, $t0, 1     #   sets t7 to i - 1
    mul $t1, $t7, 4     #   calculate &numbers[i - 1]
    add $t3, $t1, $t2   #
    lw $t5, ($t3)       #   loads numbers[i - 1] into t5 'y' 
    
    add $t0, $t0, 1     #   i++;   
    
    bge $t4, $t5, loop1 #   if (x < y) {
    
    li $t6, 1           #       swapped = 1; - return value
    
                        #   }   
                        
                        # }
end1:

    li $v0, 1           # printf("%d", swapped);
    move $a0, $t6
    syscall
    
    li $v0, 11 
    li $a0, '\n'        # printf("%c", '\n');
    syscall  

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

