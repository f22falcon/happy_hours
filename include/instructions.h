#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "cpu_struct.h"


typedef struct{
    uint8_t mod;
    uint8_t reg;
    uint8_t rm;
}ModRM;

void op_mov_rl_imm8(CPU *cpu);
void op_mov_rl_imm16(CPU *cpu);
void op_add_rm8_r8(CPU *cpu);
void op_add_rm16_r16(CPU *cpu);
void op_sub_rm8_r8(CPU *cpu);
void op_sub_rm16_r16(CPU *cpu);
void op_cmp_rm8_r8(CPU *cpu);
void op_cmp_rm16_r16(CPU *cpu);
void op_jmp_short(CPU *cpu);
void op_jz_short(CPU *cpu);
void op_jnz_short(CPU *cpu);
void op_jc_short(CPU *cpu);
void op_jnc_short(CPU *cpu);

void op_and_rm8_r8(CPU *cpu);
void op_and_rm16_r16(CPU *cpu);

void op_or_rm8_r8(CPU *cpu);
void op_or_rm16_r16(CPU *cpu);

void op_xor_rm8_r8(CPU *cpu);
void op_xor_rm16_r16(CPU *cpu);
void op_inc_r16(CPU *cpu);
void op_dec_r16(CPU *cpu);


void op_hlt(CPU *cpu);

#endif