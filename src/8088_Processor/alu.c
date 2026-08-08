#include "alu.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*----------------------------------------------------------------------
--------------------*/
/*Even parity*/
/*-------------------------------------------------------------------
------------------*/

uint16_t alu_udiv8(uint16_t dividend, uint8_t divisor)
{
    uint16_t remainder = 0;
    uint32_t temp = dividend;

    for (int i = 0; i < 16; i++)
    {
        remainder = (remainder << 1) | ((temp >> 15) & 1);

        temp <<= 1;

        if (remainder >= divisor)
        {
            remainder -= divisor;
            temp |= 1;
        }
    }

    return ((remainder & 0xFF) << 8) | (temp & 0xFF);
}



static uint32_t alu_udiv16(uint32_t dividend, uint16_t divisor)
{
    uint32_t remainder = 0;
    uint32_t temp = dividend;

    for (int i = 0; i < 32; i++)
    {
        /* Bring down MSB of dividend */
        remainder = (remainder << 1) |
                    ((temp >> 31) & 1);

        /* Shift dividend/quotient left */
        temp <<= 1;

        if (remainder >= divisor)
        {
            remainder -= divisor;
            temp |= 1;
        }
    }

    return ((remainder & 0xFFFF) << 16) |
           (temp & 0xFFFF);
}

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
        
    }
    quotient = temp & 0XFF ;  
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
int16_t alu_imul8(CPU *cpu,int8_t multiplicand ,int8_t multiplier){
    int16_t  result=0;
    int16_t mplier =(int16_t)multiplier;
    int16_t mcand =(int16_t)multiplicand;
    if (mplier <0){
        mplier =-mplier;
        mcand=-mcand;
    }
    for (int i=0;i<8;i++){
        /*if current multiplier bit is 1,add multiplicand*/
        if(mplier & 1){
            result+=mcand;
        }
        mcand<<=1;
        mplier >>=1;
    }
    if (result<-128 || result > 127 ){
        cpu->eu.flags |=(FLAG_CF|FLAG_OF);
    }
    else
        cpu->eu.flags |=~(FLAG_CF|FLAG_OF);
    /*ZF,SF,PF,AF are undefined on the real 8088*/
    return result;

}
int32_t alu_imul16(CPU *cpu,int16_t multiplicand ,int16_t multiplier){
    int32_t  result=0;
    int32_t mplier =(int32_t)multiplier;
    int32_t mcand =(int32_t)multiplicand;
    if (mplier <0){
        mplier =-mplier;
        mcand=-mcand;
    }
    for (int i=0;i<16;i++){
        /*if current multiplier bit is 1,add multiplicand*/
        if(mplier & 1){
            result+=mcand;
        }
        mcand<<=1;
        mplier >>=1;
    }
    if ( result<-32768 || result > 3267 ){
        cpu->eu.flags |=(FLAG_CF|FLAG_OF);
    }
    else
        cpu->eu.flags |=~(FLAG_CF|FLAG_OF);
    /*ZF,SF,PF,AF are undefined on the real 8088*/
    return result;

}

int16_t alu_idiv8(CPU *cpu, int16_t dividend, int8_t divisor)
{   
    (void)cpu;

    if (divisor == 0)
    {
        printf("Divide by zero!\n");
        exit(1);
    }

    int dividend_neg = (dividend < 0);
    int divisor_neg  = (divisor < 0);

    /* Promote before negating */
    int32_t temp_dividend = dividend;
    int16_t temp_divisor  = divisor;

    if (temp_dividend < 0)
        temp_dividend = -temp_dividend;

    if (temp_divisor < 0)
        temp_divisor = -temp_divisor;

    uint16_t u_dividend = (uint16_t)temp_dividend;
    uint8_t  u_divisor  = (uint8_t)temp_divisor;

    /* Restoring division WITHOUT unsigned overflow handling */
    uint16_t result = alu_udiv8(u_dividend, u_divisor);

    uint8_t u_quotient  = result & 0xFF;
    uint8_t u_remainder = result >> 8;

    /*
     * Check signed quotient range BEFORE converting
     * 0x80 to int8_t.
     */
    if (dividend_neg ^ divisor_neg)
    {
        /* Negative quotient: -128 is valid */
        if (u_quotient > 128)
        {
            printf("Divide overflow!\n");
            exit(1);
        }
    }
    else
    {
        /* Positive quotient: maximum is +127 */
        if (u_quotient > 127)
        {
            printf("Divide overflow!\n");
            exit(1);
        }
    }

    int16_t quotient  = u_quotient;
    int16_t remainder = u_remainder;

    /* Restore signs */
    if (dividend_neg ^ divisor_neg)
        quotient = -quotient;

    if (dividend_neg)
        remainder = -remainder;

    return ((uint16_t)(uint8_t)remainder << 8) |
           (uint8_t)quotient;
}

int32_t alu_idiv16(CPU *cpu, int32_t dividend, int16_t divisor)
{
    (void)cpu;

    if (divisor == 0)
    {
        printf("Divide by Zero Error!\n");
        exit(1);
    }

    int dividend_neg = (dividend < 0);
    int divisor_neg  = (divisor < 0);

    /*
     * Promote before negating.
     * This is important for -32768 and -2147483648.
     */
    int64_t temp_dividend = dividend;
    int32_t temp_divisor  = divisor;

    if (temp_dividend < 0)
        temp_dividend = -temp_dividend;

    if (temp_divisor < 0)
        temp_divisor = -temp_divisor;

    uint32_t u_dividend = (uint32_t)temp_dividend;
    uint16_t u_divisor  = (uint16_t)temp_divisor;

    /* 32-iteration restoring division */
    uint32_t result = alu_udiv16(u_dividend, u_divisor);

    uint16_t u_quotient  = result & 0xFFFF;
    uint16_t u_remainder = (result >> 16) & 0xFFFF;

    /*
     * Check signed quotient before converting
     * 0x8000 to int16_t.
     */
    if (dividend_neg ^ divisor_neg)
    {
        /* Negative quotient: -32768 is valid */
        if (u_quotient > 32768)
        {
            printf("Divide overflow!\n");
            exit(1);
        }
    }
    else
    {
        /* Positive quotient: maximum +32767 */
        if (u_quotient > 32767)
        {
            printf("Divide overflow!\n");
            exit(1);
        }
    }

    int32_t quotient  = u_quotient;
    int32_t remainder = u_remainder;

    /* Restore quotient sign */
    if (dividend_neg ^ divisor_neg)
        quotient = -quotient;

    /* Remainder follows dividend sign */
    if (dividend_neg)
        remainder = -remainder;

    return ((uint32_t)(uint16_t)remainder << 16) |
           (uint16_t)quotient;
}