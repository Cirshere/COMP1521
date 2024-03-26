// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define N_BITS 32
#define SIGN_BIT 31
#define EXP_HIGH_BIT 30
#define EXP_LOW_BIT 23
#define FRAC_HIGH_BIT 22
#define FRAC_LOW_BIT 0

uint32_t extract_bit_range(uint32_t input, int high, int low) {

    uint32_t mask = (((uint32_t)1) << (high - low + 1)) - 1;
    return (input >> low) & mask;

}

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    
    float_components_t components; 
    
    components.sign = extract_bit_range(f, SIGN_BIT, SIGN_BIT);
    components.exponent = extract_bit_range(f, EXP_HIGH_BIT, EXP_LOW_BIT);
    components.fraction = extract_bit_range(f, FRAC_HIGH_BIT, FRAC_LOW_BIT);
    
    return components;       
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {

    if (f.exponent == 255 && f.fraction != 0) {
        return 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    
    if (f.exponent == 255 && f.sign == 0 && f.fraction == 0) {
        return 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    
    if (f.exponent == 255 && f.sign == 1 && f.fraction == 0) {
        return 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {

    if (f.exponent == 0 && f.fraction == 0) {
        return 1;
    }

    return 0;
}
