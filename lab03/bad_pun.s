# Punny Program

    .text
    
main:
   
    # printf(I MIPS YOU!)   
    li $v0, 4    
    la $a0, pun
    syscall     

    #return 0
    li $v0, 0
    jr $ra   


    .data    
pun:
    .asciiz "I MIPS you!\n"
    
    
    

