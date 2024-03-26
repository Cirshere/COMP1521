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

void print_program(uint32_t bits, int i);

int main (int argc, char *argv[]) {

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    
    uint32_t filearr[1000];
    int i = 0;
    while ((fscanf (fp, "%x", &filearr[i])) != EOF) {
        i++;
    }
    
    // Array size of filearr
    int arrsize = i;        
    i = 0;    
    
    while (i < arrsize) {
        uint32_t bits = filearr[i];        
        print_program(bits, i);
        i++;
    }

    return 0;

}

void print_program(uint32_t bits, int i) {
    
    uint32_t s = (bits & s_mask) >> 21;
    uint32_t t = (bits & t_mask) >> 16;
    uint32_t d = (bits & d_mask) >> 11;
    uint32_t end = (bits & end_mask);
    int16_t I = bits & i_mask; 
    
    if (bits == 0xc) {
        printf("%3d: syscall\n", i);        
    } else if (bits >> 26 == 0 || bits >> 26 == 0x1c) {
        
        if (bits >> 26 == 0 && end == 0x2) {   // mul
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
        }    
    } 
}
