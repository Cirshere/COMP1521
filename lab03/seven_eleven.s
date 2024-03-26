# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la $a0, prompt     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall    
    move $t0, $v0       # stores v0 into t0 - input number 
    li $t1, 1           # equivalent of int i = 1

loop: # check divis          

    li $t2, 7           # t2 = 7 for calculating mod
    li $t3, 11          # t3 = 11 for calculating mod
    
    rem $t4, $t1, $t2   # i % 7 stored into t4
    beqz $t4, print     # if t4 = 0, goto print
    
    rem $t4, $t1, $t3   # i % 11 stored into t4
    beqz $t4, print     #if t4 = 0, goto print 
    
    addi $t1, $t1, 1    # i + 1
    
    blt $t1, $t0, loop
    bge $t1, $t0, end

print:
    
    li $v0, 1           # printf (%d, i);
    move $a0, $t1       
    syscall
    
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall 
    
    addi $t1, $t1, 1
    
    blt $t1, $t0, loop

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter a number: "
