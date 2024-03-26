#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define LEAST 0xff
#define SEC_LEAST 0xff00 

// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int final_q2(uint32_t value) {
    
    uint32_t least =  value & LEAST;
    uint32_t sec_least = value & SEC_LEAST;
    sec_least = sec_least >> 8;
    
    if (least == sec_least) {
        return 1;
    }

    return 0;
}
