// Reads a file line by line, taking 32-bit opcodes and emulates 
// the output of assembly
// Christopher Hoang, z5259780
// 04/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define S_MASK 0x1f << 21
#define T_MASK 0x1f << 16
#define D_MASK 0x1f << 11 
#define I_MASK 0xffff
#define END_MASK 0x3f



#define $V0 2
#define $A0 4
#define PRINT_INT 1
#define PRINT_CHAR 11
#define EXIT 10
#define REG_SIZE 32

int opcode_d(uint32_t bits, int i, uint32_t d, uint32_t arr[]);
int opcode_i_return(uint32_t bits, int i, uint32_t arr[], uint32_t t);
int opcode_branching(uint32_t bits, int i, uint32_t arr[], int size);
void print_program(int size, char *filename, uint32_t file[]);
void print_output(int i, int arr[]);
void print_registers(uint32_t arr[], int i);

int main (int argc, char *argv[]) {

    // Open filename
    char *filename = argv[1];    
    FILE *fp = fopen(filename, "r");

    // Array for registers
    uint32_t registers[REG_SIZE] = {0};
    
    // Array for storing file
    uint32_t filearr[1000];
    
    int i = 0;
    while ((fscanf (fp, "%x", &filearr[i])) != EOF) {
        i++;
    }
    

    // Array for storing syscall values
    int syscall[350];
    int k = 0;
    int offset = 0;
    uint32_t bits;

    // Array size of filearr
    int arrsize = i;
    i = 0;
        
    while (i < arrsize) { 
        bits = filearr[i];
     
        // syscall
        if (bits == 0xc) {                  
            if (registers[$V0] == EXIT){     // exit
                break;
            } else if (registers[$V0] != PRINT_INT && 
            registers[$V0] != PRINT_CHAR) {
                syscall[k] = registers[$V0];         // 0 & even = $v0
                syscall[k + 1] = registers[$A0];     // odd = $a0
                k += 2;                
                break;
            }
            syscall[k] = registers[$V0];         // 0 & even = $v0
            syscall[k + 1] = registers[$A0];     // odd = $a0            
            k += 2;
        // add, sub, and, or, slt, mul
        } else if ((bits >> 26 == 0) || (bits >> 26 == 0x1c)) {
            uint32_t d = (bits & D_MASK) >> 11;            
            registers[d] = opcode_d(bits, i, d,registers);    
        // bne, beq        
        } else if ((bits >> 26 == 0x04) || (bits >> 26 == 0x05)) {
            offset = opcode_branching (bits, i, registers, arrsize);
            i += offset;  
        // addi, slti, andi, ori, lui                  
        } else {
            uint32_t t = (bits & T_MASK) >> 16;
            registers[t] = opcode_i_return(bits, i, registers, t);            
        }
                
        registers[0] = 0;    
        if (offset == 0) {
            i++;
        }
        offset = 0;
    } 

    printf("Program\n");    
    print_program(arrsize, filename, filearr);
    
    printf("Output\n");
    for (i = 0; i < k; i += 2) {
        print_output(i, syscall);
    }
    
    printf ("Registers After Execution\n");
    for (i = 0; i < REG_SIZE; i++) {
        print_registers(registers, i);
    }
    
    fclose(fp);
    
    return 0;
}   

// Function includes add, sub, and, or, slt, mul
int opcode_d(uint32_t bits, int i, uint32_t d, uint32_t arr[]) {

    uint32_t end = bits & END_MASK;
    uint32_t s = (bits & S_MASK) >> 21;
    uint32_t t = (bits & T_MASK) >> 16;
    
    int result = 0;
    
    if (bits >> 26 == 0x1c && end == 0x2) {   // mul
        result = arr[s] * arr[t];
        return result;
    }
    
    if (end == 0x20) {          // add
        result = arr[s] + arr[t];
        
    } else if (end == 0x22) {   // sub
        result = arr[s] - arr[t];
        
    } else if (end == 0x24) {   // and
        result = arr[s] & arr[t];
        
    } else if (end == 0x25) {   // or
        result = arr[s] | arr[t];
        
    } else if (end == 0x2a) {   // slt
        if (arr[s] < arr[t]) {
            result = 1;
        }
    }
    
    return result;
}

// Function includes addi, slti, andi, ori, lui
int opcode_i_return(uint32_t bits, int i, uint32_t arr[], uint32_t t) {

    uint32_t s = (bits & S_MASK) >> 21;
    int16_t I = (bits & I_MASK);
    
    uint32_t result = 0;
    
    if (bits >> 26 == 0x08) {           // addi
        result = arr[s] + I;
    } else if (bits >> 26 == 0x0a) {    // slti
        result = arr[s] < I;
    } else if (bits >> 26 == 0x0c) {    // andi
        result = arr[s] & I;
    } else if (bits >> 26 == 0x0d) {    // ori 
        result = (arr[s] | I);
    } else if (bits >> 21 == 0x1e0) {    // lui
        result = (I << 16);
    }
    
    return result;
}

// Function includes beq, bne
int opcode_branching(uint32_t bits, int i, uint32_t arr[], int size) {
    
    uint32_t s = (bits & S_MASK) >> 21;
    uint32_t t = (bits & T_MASK) >> 16;
    int16_t I = (bits & I_MASK);
    
    if (bits >> 26 == 0x04) {                   // beq
        if (arr[s] == arr[t]) {
            if (i + I < 0 || i + I > size) {
                exit(0);
            } 
            return I;            
        }      
        
    } else if (bits >> 26 == 0x05) {           // bne
        if (arr[s] != arr[t]) {
            if(i + I < 0 || i + I > size) {
                exit(0);
            }
            return I;
        }
    }
    
    return 0;

}

// Function prints the output line for program
void print_program(int size, char *filename, uint32_t file[]) {
    
    for (int i = 0; i < size; i++) {
        uint32_t bits = file[i];
        
        uint32_t s = (bits & S_MASK) >> 21;
        uint32_t t = (bits & T_MASK) >> 16;
        uint32_t d = (bits & D_MASK) >> 11;
        uint32_t end = (bits & END_MASK);
        int16_t I = bits & I_MASK; 
        
        if (bits == 0xc) {
            printf("%3d: syscall\n", i);        
        } else if (bits >> 26 == 0 || bits >> 26 == 0x1c) {
            
            if (bits >> 26 == 0x1c && end == 0x2) {   // mul
                printf ("%3d: mul  $%d, $%d, $%d\n", i, d, s, t);
            }
            
            if (end == 0x20) {          // add
                printf ("%3d: add  $%d, $%d, $%d\n", i, d, s, t);
                
            } else if (end == 0x22) {   // sub
                printf ("%3d: sub  $%d, $%d, $%d\n", i, d, s, t);
                
            } else if (end == 0x24) {   // and
                printf ("%3d: and  $%d, $%d, $%d\n", i, d, s, t);
                
            } else if (end == 0x25) {   // or
                printf ("%3d: or   $%d, $%d, $%d\n", i, d, s, t);
                
            } else if (end == 0x2a) {   // slt
                printf ("%3d: slt  $%d, $%d, $%d\n", i, d, s, t);
            }    
            
        } else if (bits >> 26 == 0x04|| bits >> 26 == 0x05) {
        
            if (bits >> 26 == 0x04) {                   // beq
                printf("%3d: beq  $%d, $%d, %d\n", i, s, t, I);           
            } else if ( bits >> 26 == 0x05) {           // bne
                printf("%3d: bne  $%d, $%d, %d\n", i, s, t, I);
            }         
        } else {
        
            if (bits >> 26 == 0x08) {           // addi
                printf("%3d: addi $%d, $%d, %d\n", i, t, s, I );
            } else if (bits >> 26 == 0x0a) {    // slti
                printf("%3d: slti $%d, $%d, %d\n", i, t, s, I );
            } else if (bits >> 26 == 0x0c) {    // andi
                printf("%3d: andi $%d, $%d, %d\n", i, t, s, I );
            } else if (bits >> 26 == 0x0d) {    // ori 
                printf("%3d: ori  $%d, $%d, %d\n", i, t, s, I );
            } else if (bits >> 21 == 0x1e0) {    // lui
                printf("%3d: lui  $%d, %d\n", i, t, I);
            } else {
                printf("%s:%d: invalid instruction code: %08x", filename, i, bits);
            }
        }
    
    } 
}

// Function prints output

void print_output(int i, int arr[]) {
    
    if (arr[i] == PRINT_INT) {          // print int
        printf("%d", arr[i + 1]);
    } else if (arr[i] == PRINT_CHAR) {  // print char
        printf("%c", arr[i + 1]);
    } else {
        printf("Unknown system call: %d\n", arr[i]);
    }
    
}

// Function prints registers after execution

void print_registers(uint32_t arr[], int i) {

    if (arr[i] != 0) {
        printf("$%-2d = %d\n", i, arr[i]);
    }
   
}
