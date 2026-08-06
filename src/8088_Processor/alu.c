#include "alu.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

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
uint16_t alu_mul8(CPU *cpu,uint8_t multiplicand ,uint8_t multiplier){
    uint16_t  result=0;
    uint16_t mcand=multiplicand;
    for (int i=0;i<8;i++){
        /*if current multiplier bit is 1,add multiplicand*/
        if(multiplier & 0x01){
            result+=mcand;
        }
        mcand <<=1;
        multiplier >>=1;
    }
    if (result & 0xFF00){
        cpu->eu.flags |=(FLAG_CF|FLAG_OF);
    }
    else
        cpu->eu.flags |=~(FLAG_CF|FLAG_OF);
    /*ZF,SF,PF,AF are undefined on the real 8088*/
    return result;

}
uint32_t alu_mul16(CPU *cpu,uint16_t multiplicand ,uint16_t multiplier){
    uint32_t  result=0;
    uint32_t mcand=multiplicand;
    for (int i=0;i<16;i++){
        /*if current multiplier bit is 1,add multiplicand*/
        if(multiplier & 0x01){
            result+=mcand;
        }
        mcand <<=1;
        multiplier >>=1;
    }
    if (result & 0xFFFF0000)
        cpu->eu.flags |=(FLAG_CF|FLAG_OF);
    else
        cpu->eu.flags |=~(FLAG_CF|FLAG_OF);
    /*ZF,SF,PF,AF are undefined on the real 8088*/
    return result;

}

uint16_t alu_div8(CPU *cpu ,uint16_t dividend ,uint8_t divisor){
    (void)cpu;
    if(divisor ==0){
        printf("Devide by Zero Error!\n");
        exit(1);
    }
    uint16_t  remainder=0;
    uint32_t temp = dividend;
    uint8_t quotient;
    for (int i=0;i<16;i++){
        /*Shift remainder left and bring in MSB of dividend*/
        remainder=(remainder << 1)|((temp>>15)&1);
        /*Shift dividend left (quotient  is built here)*/
        temp<<=1;
        if(remainder >= divisor){
            remainder-=divisor;
            temp|=1;
        }
    quotient = temp & 0XFF ;   
        
    }
    if (temp & 0xFF00){
        printf("Divide overflow!\n");
        exit(1);
    }
    return ((uint16_t)remainder<<8)|quotient;
}

uint32_t alu_div16(CPU *cpu ,uint32_t dividend ,uint16_t divisor){
    (void)cpu;
    if(divisor ==0){
        printf("Devide by Zero Error!\n");
        exit(1);
    }
    uint32_t  remainder=0;
    uint32_t temp = dividend;
    for (int i=0;i<32;i++){
        /*Shift remainder left and bring in MSB of dividend*/
        remainder=(remainder << 1)|((temp>>31)&1);
        /*Shift dividend left (quotient  is built here)*/
        temp<<=1;
        if(remainder >= divisor){
            remainder-=divisor;
            temp|=1;
        }
      
        
    }
    if (temp & 0xFFFF0000){
        printf("Divide overflow!\n");
        exit(1);
    }
    return ((remainder<<16)|(temp & 0xFFFF));
}