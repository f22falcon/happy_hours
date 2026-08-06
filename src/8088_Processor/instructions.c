#include "instructions.h"
#include "alu.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
void op_group_f6(CPU *cpu){
    uint8_t modrm = biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    switch (m.reg){
        case 4:
          op_mul8(cpu,m);
          break;
        case 5:
          op_imul8(cpu,m);
          break;
        case 6:
          op_div8(cpu,m);
          break;
        case 7:
          op_idiv8(cpu,m);
          break;
    }
}
void op_group_f7(CPU *cpu){
    uint8_t modrm = biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    switch (m.reg){
        case 4:
          op_mul16(cpu,m);
          break;
        case 5:
          op_imul16(cpu,m);
          break;
        case 6:
          op_div16(cpu,m);
          break;
        case 7:
          op_idiv16(cpu,m);
          break;
    }
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


void op_and_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint8_t *dst =eu_get_reg8(&cpu->eu,m.rm);
        uint8_t *src =eu_get_reg8(&cpu->eu,m.reg);
        *dst=
        alu_and8(
            cpu,
            *dst,
            *src
          );
          
    }
}

void op_and_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_and16(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_or_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_or8(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_or_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_or16(
            cpu,
            *dst,
            *src
          );
          
    }
}

void op_xor_rm8_r8(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_xor8(
            cpu,
            *dst,
            *src
          );
          
    }
}
void op_xor_rm16_r16(CPU *cpu){
    uint8_t modrm =biu_fetch8(cpu);
    ModRM m = decode_modrm(modrm);
    /*
    00 D8 = ADD AL,BL*/
    if (m.mod ==3){
        uint16_t *dst =eu_get_reg16(&cpu->eu,m.rm);
        uint16_t *src =eu_get_reg16(&cpu->eu,m.reg);
        *dst =
          alu_xor16(
            cpu,
            *dst,
            *src
          );
          
    }
}

void op_inc_r16(CPU *cpu){
    uint8_t reg = cpu->eu.IR-0x40;
    uint16_t *dst = eu_get_reg16(&cpu->eu,reg);
    *dst=alu_inc16(cpu,*dst);

}

void op_dec_r16(CPU *cpu){
    uint8_t reg = cpu->eu.IR-0x48;
    uint16_t *dst = eu_get_reg16(&cpu->eu,reg);
    *dst=alu_dec16(cpu,*dst);

}

void op_mul8(CPU *cpu,ModRM m){
    
    if (m.mod !=3){
        printf("MUL r/m8 memory  operand not implemented!\n");
        exit(1);
    }
    uint8_t *src= eu_get_reg8(&cpu->eu,m.rm);
    uint16_t result = alu_mul8(cpu,cpu->eu.AX.byte.low,*src);
    cpu->eu.AX.reg=result;

}
void op_imul8(CPU *cpu,ModRM m){
    (void)cpu;
    (void)m;
}
void op_div8(CPU *cpu,ModRM m){
    if (m.mod !=3){
        printf("DIV r/m8 memory  operand not implemented!\n");
        exit(1);
    }
    uint8_t *src =eu_get_reg8(&cpu->eu,m.rm);
    uint16_t result = alu_div8(cpu,cpu->eu.AX.reg, *src);
    /*Quotient -> AL*/
    cpu->eu.AX.byte.low =(uint8_t)(result & 0x00FF);
    /*Reminder -> AH*/
    cpu->eu.AX.byte.High =(uint8_t)(result >> 8);
}
void op_idiv8(CPU *cpu,ModRM m){
    (void)cpu;
    (void)m;
}

void op_mul16(CPU *cpu ,ModRM m){
   if (m.mod !=3){
        printf("MUL r/m8 memory  operand not implemented!\n");
        exit(1);
    }
    uint16_t *src= eu_get_reg16(&cpu->eu,m.rm);
    uint32_t result = alu_mul16(cpu,cpu->eu.AX.reg,*src);
    cpu->eu.AX.reg=(uint16_t)result;
    cpu->eu.DX.reg=(uint16_t)(result >> 16);

}
void op_imul16(CPU *cpu,ModRM m){
    (void)cpu;
    (void)m;
}
void op_div16(CPU *cpu,ModRM m){
    if (m.mod !=3){
        printf("MUL r/m8 memory  operand not implemented!\n");
        exit(1);
    }
    uint16_t *src = eu_get_reg16(&cpu->eu, m.rm);

    uint32_t dividend =
        ((uint32_t)cpu->eu.DX.reg << 16) |
         cpu->eu.AX.reg;

    uint32_t result = alu_div16(cpu, dividend, *src);

    cpu->eu.AX.reg = (uint16_t)(result & 0xFFFF);        // Quotient
    cpu->eu.DX.reg = (uint16_t)(result >> 16);           // Remainder
}
void op_idiv16(CPU *cpu,ModRM m){
    (void)cpu;
    (void)m;
}


void op_jmp_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    cpu->biu.ip+=disp;

}
void op_jc_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    if (cpu->eu.flags & FLAG_CF)
      cpu->biu.ip+=disp;

}
void op_jnc_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    if(!(cpu->eu.flags  & FLAG_CF))
      cpu->biu.ip+=disp;

}
void op_jz_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    if((cpu->eu.flags  & FLAG_ZF))
      cpu->biu.ip+=disp;

}
void op_jnz_short(CPU *cpu){
    int8_t disp =(int8_t)biu_fetch8(cpu);
    if(!(cpu->eu.flags  & FLAG_ZF))
      cpu->biu.ip+=disp;

}


void op_hlt(CPU *cpu){
    cpu->halted =true;
}

