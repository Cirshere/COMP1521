#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    
    while (n_rotations > 16 || n_rotations < 0) {
    
        if (n_rotations > 0) {
            n_rotations -= 16;
        } else {
            n_rotations += 16;
        }
    
    }
    
    uint16_t temp1;
    uint16_t temp2;
    uint16_t new;
    

    temp1 = (bits <<  n_rotations);
    temp2 = (bits >> (16 - n_rotations));
    
    new = temp1 | temp2;
    
    
    return new;
}
