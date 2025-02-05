#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define s_mask 0x1f << 21
#define t_mask 0x1f << 16
#define d_mask 0x1f << 11 
#define i_mask 0xffff
#define end_mask 0x3f

// Acsii 10 /LF = newline

int opcode_d(uint32_t bits, int i, uint32_t d, uint32_t arr[]);
int opcode_i_return(uint32_t bits, int i, uint32_t arr[], uint32_t t);
void opcode_branching(uint32_t bits, int offset, int i, uint32_t arr[], int size);
void print_registers(uint32_t arr[]);

int main (int argc, char *argv[]) {

    // Open filename
    char *filename = argv[1];    
    FILE *fp = fopen(filename, "r");

    // Array for registers
    uint32_t registers[32] = {0};
    
    // Array for storing file
    uint32_t filearr[1000];
    
    int i = 0;
    while ((fscanf (fp, "%x", &filearr[i])) != EOF) {
        i++;
    }
    
    int arrsize = i;
    // Used for branching
    int offset = 0;
        
    uint32_t bits;
    i = 0;
    
    printf("Program\n");
    
    for (i = 0; i < arrsize; i++) { 
        bits = filearr[i + offset];
        
        if (bits == 0xc) {
            printf("%3d: syscall\n", i);        
        } else if (bits >> 26 == 0 || bits >> 26 == 0x1c) {
            uint32_t d = (bits & d_mask) >> 11;            
            registers[d] = opcode_d(bits, i, d,registers);
        } else if (bits >> 26 == 0x04|| bits >> 26 == 0x05) {
            opcode_branching (bits, offset, i, registers, arrsize);
        
        
        } else {
            uint32_t t = (bits & t_mask) >> 16;
            registers[t] = opcode_i_return(bits, i, registers, t);
        }
        
        registers[0] = 0;
        print_registers(registers);    
    }
    
    print_registers(registers);
        
    return 0;
}

// Function includes add, sub, and, or, slt, mul
int opcode_d(uint32_t bits, int i, uint32_t d, uint32_t arr[]) {

    uint32_t end = bits & end_mask;
    uint32_t s = (bits & s_mask) >> 21;
    uint32_t t = (bits & t_mask) >> 16;
    
    int result = 0;
    
    if (bits >> 26 == 0 && end == 0x2) {   // mul
        result = arr[s] * arr[t];
        printf ("%3d: mul  $%d, $%d, $%d\n", i, d, s, t);
        return result;
    }
    
    if (end == 0x20) {          // add
        result = arr[s] + arr[t];
        printf ("%3d: add  $%d, $%d, $%d\n", i, d, s, t);
        
    } else if (end == 0x22) {   // sub
        result = arr[s] - arr[t];
        printf ("%3d: sub  $%d, $%d, $%d\n", i, d, s, t);
        
    } else if (end == 0x24) {   // and
        result = arr[s] & arr[t];
        printf ("%3d: and  $%d, $%d, $%d\n", i, d, s, t);
        
    } else if (end == 0x25) {   // or
        result = arr[s] | arr[t];
        printf ("%3d: or   $%d, $%d, $%d\n", i, d, s, t);
        
    } else if (end == 0x2a) {   // slt
        if (arr[s] < arr[t]) {
            result = 1;
        }
        printf ("%3d: slt  $%d, $%d, $%d\n", i, d, s, t);
    }
    
    return result;
}

// Function includes addi, slti, andi, ori, lui
int opcode_i_return(uint32_t bits, int i, uint32_t arr[], uint32_t t) {

    uint32_t s = (bits & s_mask) >> 21;
    int16_t I = (bits & i_mask);
    
    uint32_t result = 0;
    
   
    if (bits >> 26 == 0x08) {           // addi
        result = arr[s] + I;
        printf("%3d: addi $%d, $%d, %d\n", i, t, s, I );
    } else if (bits >> 26 == 0x0a) {    // slti
        result = arr[s] < I;
        printf("%3d: slti $%d, $%d, %d\n", i, t, s, I );
    } else if (bits >> 26 == 0x0c) {    // andi
        result = arr[s] & I;
        printf("%3d: andi $%d, $%d, %d\n", i, t, s, I );
    } else if (bits >> 26 == 0x0d) {    // ori 
        result = (arr[s] | I);
        printf("%3d: ori  $%d, $%d, %d\n", i, t, s, I );
    } else if (bits >> 21 == 0x1e0) {    // lui
        result = (I << 16);
        printf("%3d: lui  $%d, %d\n", i, t, I);
    }
    
    return result;
}

// Function includes beq, bne
void opcode_branching(uint32_t bits, int offset, int i, uint32_t arr[], int size) {
    
    uint32_t s = (bits & s_mask) >> 21;
    uint32_t t = (bits & t_mask) >> 16;
    int16_t I = bits & i_mask;
       
    
    if (bits >> 26 == 0x04) {                   // beq
        if (arr[s] == arr[t]) {
            if (i + offset < 0 || i + offset > size) {
                exit(0);
            }
            offset = I;                
        }
        printf("%3d: beq  $%d, $%d, %d\n", i, s, t, I);
        
        
    } else if ( bits >> 26 == 0x05) {           // bne
        if (arr[s] != arr[t]) {    
            if (i + offset < 0 || i + offset > size) {
                exit(0);
            }
        }
        offset = I;
        
        printf("%3d: bne  $%d, $%d, %d\n", i, s, t, I);
    }

}

// Function prints registers after execution

void print_registers(uint32_t arr[]) {
    
    printf ("Registers After Execution\n");
    
    for (int i = 0; i < 32; i++) {
        if (arr[i] != 0) {
            printf("$%-2d = %d\n", i, arr[i]);
        }
    }    
}
