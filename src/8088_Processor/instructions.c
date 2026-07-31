#include "instructions.h"
#include "alu.h"
#include "Biu.h"




void op_mov_al_imm8(CPU *cpu){
    cpu->eu.AX.byte.low=biu_fetch8(cpu);
}


void op_mov_bl_imm8(CPU *cpu){
    cpu->eu.BX.byte.low=biu_fetch8(cpu);
}


void op_add_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    /*
    00 D8 = ADD AL,BL*/
    if (modrm ==0xD8){
        cpu->eu.AX.byte.low =
          alu_add8(
            cpu,
            cpu->eu.AX.byte.low, 
            cpu->eu.BX.byte.low
          );
    }
}



void op_hlt(CPU *cpu){
    cpu->halted =true;
}

