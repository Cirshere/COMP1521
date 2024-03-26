# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall
    move $t0, $v0       # stores scanf in into t0

    # If mark >= 50, goto pass
    li      $t1, 50
    bge     $t0, $t1, pass  

    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall


    jr $ra              # return

pass:
    
    li $t1, 6
    bge $t0, $t1, credit # if mark >= 65 goto credit
    
    li $v0, 4
    la $a0, ps           # else print PS 
    syscall
    
    j end
    
credit:
    
    li $t1, 75
    bge $t0, $t1, distinction  # if mark >= 75 goto distinction
    
    li $v0, 4
    la $a0, cr                 # else print CR
    syscall
    
    j end
    
distinction:

    li $t1, 85
    bge $t0, $t1, hg_distinction    # if mark >= 85 goto high distinction
    
    li $v0, 4
    la $a0, dn                      # else print DN
    syscall
    
    j end
    
hg_distinction:

    li $v0, 4
    la $a0, hd      # print HD
    syscall
    
    j end

end: 

    li $v0, 0
    jr $ra

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
