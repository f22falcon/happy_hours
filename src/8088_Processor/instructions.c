#include "instructions.h"
#include "alu.h"
#include <stddef.h>
#include <stdio.h>
#include "cpu_struct.h"
#include "Biu.h"


static ModRM decode_modrm(uint8_t modrm)
{
    ModRM m;
    m.mod =(modrm >> 6)& 0x03;
    m.reg =(modrm >> 3)& 0x07;
    m.rm = modrm & 0x07;

    return m;

}


static uint8_t *eu_get_reg8(EU *eu,uint8_t reg )
{
    switch(reg){
        case 0:return &eu->AX.byte.low;
        case 1:return &eu->CX.byte.low;
        case 2:return &eu->DX.byte.low;
        case 3:return &eu->BX.byte.low;
        case 4:return &eu->AX.byte.High;
        case 5:return &eu->CX.byte.High;
        case 6:return &eu->DX.byte.High;
        case 7:return &eu->BX.byte.High;
    }
    return NULL;
}

static uint16_t *eu_get_reg16(EU *eu,uint8_t reg )
{
    switch(reg){
        case 0:return &eu->AX.reg;
        case 1:return &eu->CX.reg;
        case 2:return &eu->DX.reg;
        case 3:return &eu->BX.reg;
        case 4:return &eu->sp;
        case 5:return &eu->bp;
        case 6:return &eu->si;
        case 7:return &eu->di;
    }
    return NULL;
}
void op_mov_rl_imm16(CPU *cpu){ 
    uint8_t reg= cpu->eu.IR - 0xB8;
    uint16_t *dst =eu_get_reg16(&cpu->eu,reg);
    *dst = biu_fetch16(cpu);

}

void op_mov_rl_imm8(CPU *cpu){ 
    uint8_t reg= cpu->eu.IR - 0xB0;
    uint8_t *dst =eu_get_reg8(&cpu->eu,reg);
    *dst = biu_fetch8(cpu);

}


void op_add_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint8_t *dst =eu_get_reg8(&cpu->eu,m.rm);
        uint8_t *src =eu_get_reg8(&cpu->eu,m.reg);
        *dst =
          alu_add8(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_sub_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint8_t *dst =eu_get_reg8(&cpu->eu,m.rm);
        uint8_t *src =eu_get_reg8(&cpu->eu,m.reg);
        *dst =
          alu_sub8(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_cmp_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint8_t *dst =eu_get_reg8(&cpu->eu,m.rm);
        uint8_t *src =eu_get_reg8(&cpu->eu,m.reg);
        alu_sub8(
            cpu,
            *dst,
            *src
          );
          
    }
}

void op_add_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_add16(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_cmp_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        alu_sub16(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_sub_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_sub16(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_jmp_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    cpu->biu.ip+=disp;

}


void op_hlt(CPU *cpu){
    cpu->halted =true;
}

