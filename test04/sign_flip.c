#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {

    uint32_t mask = (uint32_t)1 << 31;
    uint32_t new = 0;
    
    mask = (mask & f);
    
    if (mask == 0) {
    
        mask = (uint32_t)1 << 31;        
        new = f | mask;
        
    } else if (mask != 0) {
     
        mask = ~((uint32_t)1 << 31);
        new = mask & f;
        
       
    }
    

    return new;
}
