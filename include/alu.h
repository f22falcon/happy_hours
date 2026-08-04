#ifndef ALU_H
#define ALU_H
#include <stdint.h>
#include <stdbool.h>
#include "cpu_struct.h"

//Flags helper mask definations for 8088Flags register 
# define FLAG_CF (1<<0) //Carry Flag
# define FLAG_PF (1<<2) //Parity Flag
# define FLAG_AF (1<<4) //Auxilliary Carry Flag
# define FLAG_ZF (1<<6) //Zero Flag
# define FLAG_SF (1<<7) //Sign  Flag
# define FLAG_OF (1<<11) //Overflow Flag

//Alu operation (8-bit and 16-bit)
uint8_t alu_add8(CPU *cpu ,uint8_t a ,uint8_t b);
uint16_t alu_add16(CPU *cpu ,uint16_t a ,uint16_t b);

uint8_t alu_sub8(CPU *cpu ,uint8_t a ,uint8_t b);
uint16_t alu_sub16(CPU *cpu ,uint16_t a ,uint16_t b);

uint8_t alu_and8(CPU *cpu ,uint8_t a ,uint8_t b);
uint16_t alu_and16(CPU *cpu ,uint16_t a ,uint16_t b);

uint8_t alu_or8(CPU *cpu ,uint8_t a ,uint8_t b);
uint16_t alu_or16(CPU *cpu ,uint16_t a ,uint16_t b);

uint8_t alu_xor8(CPU *cpu ,uint8_t a ,uint8_t b);
uint16_t alu_xor16(CPU *cpu ,uint16_t a ,uint16_t b);

uint8_t alu_not8(uint8_t value );
uint16_t alu_not16(uint16_t value);

uint16_t alu_inc16(CPU *cpu,uint16_t value);
uint16_t alu_dec16(CPU *cpu,uint16_t value);


//Helper function to evaluate sign flags and zero flags

void alu_update_sz_flags8(CPU *cpu,uint8_t result);
void alu_update_sz_flags16(CPU *cpu,uint16_t result);

#endif



