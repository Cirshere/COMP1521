// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    uint32_t result = 0;  

    uint16_t ui;
    ui = i;
    
    result = result | (ui);
    
    int32_t ut;
    ut = t;

    result = result | (ut << 16);  

    uint32_t us;    
    us = s;  
    
    result = result | (us << 21);
    
    result = result | (0x2u << 28);
    
    return result;

}
