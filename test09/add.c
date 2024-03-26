#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {

    uint32_t op = 0;
    
    op |= (s << 21);
    op |= (t << 16);
    op |= (d << 11);
    op |= (0x1u << 5);

    return op; // REPLACE WITH YOUR CODE

}
