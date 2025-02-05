// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define N_BITS 64 

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    
    int total = 0; 

    uint64_t mask;

    for (int i = 0; i < N_BITS; i++) {
    
        mask = (uint64_t)1 << i;
        
        if ((value & mask) != 0) {
            total++;        
        }    
        
    }

    return total;
}
