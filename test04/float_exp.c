#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {

    uint32_t exponent;    
    uint32_t mask;

    mask = (((uint32_t)1) << (30 - 23 + 1)) - 1;
    
    exponent = (f >> 23) & mask;   

    return exponent;
}
