// Christopher Hoang, z5259780
// 09/06/2020
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    int16_t new = 0;     
    int16_t mask;  
    
    // Start from bit 0 and go left
    for (int i = 0; bits[i] != '\0'; i++) {          
        
        if (bits[i] != '0') {
            // Theres a 1
            mask = 1 << (N_BITS - 1 - i);
            new = new | mask;
                        
        } else {
            // Theres a 0    
        }              
    }

    return new;
}

