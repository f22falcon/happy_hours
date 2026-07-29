#include "alu.h"


/*----------------------------------------------------------------------
--------------------*/
/*Even parity*/
/*-------------------------------------------------------------------
------------------*/

static bool even_parity(uint8_t value){
    bool parity =true;
    while(value){
        if(value & )
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
                       FLAG_OF);
    /*Carry*/
    if(temp >0xFF)
       cpu->eu.flags | FLAG_CF;
    /*Auxiliary Carry*/
    if(((a & 0x0F)+(b & 0x0F)))
        cpu->eu.flags |= FLAG_AF;
    /*Overflow*/
    if((~(a^b) & (a^result) & 0x80) )
         cpu->eu.flags| FLAG_OF;
    alu_update_sz_flags8(cpu, result);
    return result;
}