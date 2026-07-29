#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

void op_mov_al_imm8(CPU *cpu);
void op_mov_bl_imm8(CPU *cpu);
void op_add_rm8_r8(CPU *cpu);
void op_hlt(CPU *cpu);

#endif