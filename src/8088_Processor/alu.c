#include "alu.h"
#include <stdio.h>

/*----------------------------------------------------------------------
--------------------*/
/*Even parity*/
/*-------------------------------------------------------------------
------------------*/

static bool even_parity(uint8_t value){
    bool parity =true;
    while(value){
        if(value & 1)
           parity =!parity;
        value >>=1;
    }
    return parity;
}

uint8_t alu_add8(CPU *cpu,uint8_t a, uint8_t b){
    uint16_t temp = (uint16_t)a +(uint16_t)b;
    uint8_t result = (uint8_t)temp;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    /*Carry*/
    if(temp >0xFF)
       (cpu->eu.flags |= FLAG_CF);
    /*Auxiliary Carry*/
    if(((a & 0x0F)+(b & 0x0F))>0x0F)
        (cpu->eu.flags |= FLAG_AF);
    /*Overflow*/
    if((~(a^b) & (a^result) & 0x80) )
         cpu->eu.flags|= FLAG_OF;
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}

uint16_t alu_add16(CPU *cpu,uint16_t a, uint16_t b){
    uint32_t temp = (uint32_t)a +(uint32_t)b;
    uint16_t result = (uint16_t)temp;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    /*Carry*/
    if(temp >0xFFFF)
       (cpu->eu.flags |= FLAG_CF);
    /*Auxiliary Carry*/
    if(((a & 0x000F)+(b & 0x000F))>0xFF)
        (cpu->eu.flags |= FLAG_AF);
    /*Overflow*/
    if((~(a^b) & (a^result) & 0x8000) )
         cpu->eu.flags|= FLAG_OF;
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x8000)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}

uint8_t alu_sub8(CPU *cpu,uint8_t a, uint8_t b){
    uint16_t temp = (uint16_t)a -(uint16_t)b;
    uint8_t result = (uint8_t)temp;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    /*Carry(Borrow)*/
    if(a<b)
       (cpu->eu.flags |= FLAG_CF);
    /*Auxiliary Carry*/
    if(((a & 0x0F)<(b & 0x0F)))
        (cpu->eu.flags |= FLAG_AF);
    /*Overflow*/
    if(((a^b) & (a^result) & 0x80) )
         cpu->eu.flags|= FLAG_OF;
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}

uint16_t alu_sub16(CPU *cpu,uint16_t a, uint16_t b){
    uint32_t temp = (uint32_t)a -(uint32_t)b;
    uint16_t result = (uint16_t)temp;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    /*Carry(Borrow)*/
    if(a<b)
       (cpu->eu.flags |= FLAG_CF);
    /*Auxiliary Carry(Borrow)*/
    if(((a & 0x000F)<(b & 0x000F)))
        (cpu->eu.flags |= FLAG_AF);
    /*Overflow*/
    if(((a^b) & (a^result) & 0x8000) )
         cpu->eu.flags|= FLAG_OF;
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x8000)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}

uint8_t alu_or8(CPU *cpu,uint8_t a, uint8_t b){
    uint8_t result = a | b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint16_t alu_or16(CPU *cpu,uint16_t a, uint16_t b){
    uint16_t result = a | b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint8_t alu_xor8(CPU *cpu,uint8_t a, uint8_t b){
    uint8_t result = a ^ b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint16_t alu_xor16(CPU *cpu,uint16_t a, uint16_t b){
    uint16_t result = a ^ b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint8_t alu_and8(CPU *cpu,uint8_t a, uint8_t b){
    uint8_t result = a & b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint16_t alu_and16(CPU *cpu,uint16_t a, uint16_t b){
    uint16_t result = a & b;
    cpu->eu.flags &=~(FLAG_CF|
                       FLAG_AF|
                       FLAG_PF|
                       FLAG_OF|
                       FLAG_ZF|
                       FLAG_SF);                      
    
    /*Parity flag*/    
    if (even_parity(result))
        cpu->eu.flags |= FLAG_PF;
    /*Zero flag*/
    if (result == 0)
        cpu->eu.flags |=FLAG_ZF;
    /*Sign flag*/
    if (result & 0x80)
        cpu->eu.flags |=FLAG_SF;
    
    // alu_update_sz_flags8(cpu, result);
    return result;
}
uint8_t alu_not8(uint8_t value){
    
    return ~value;
}
uint16_t alu_not16(uint16_t value){
    
    return ~value;
}
uint16_t alu_inc16(CPU *cpu,uint16_t value){
    uint16_t old_cf=cpu->eu.flags & ~FLAG_CF;
    uint16_t result =alu_add16(cpu,value,1);
    cpu->eu.flags = (cpu->eu.flags & ~FLAG_CF)|old_cf;
    return result;

}
uint16_t alu_dec16(CPU *cpu,uint16_t value){
    uint16_t old_cf=cpu->eu.flags & ~FLAG_CF;
    uint16_t result =alu_sub16(cpu,value,1);
    cpu->eu.flags = (cpu->eu.flags & ~FLAG_CF)|old_cf;
    return result;

}