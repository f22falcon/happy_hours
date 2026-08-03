#include <stdio.h>

#include "Decoder_test.h"
#include "alu.h"
#include "cpu_struct.h"
#include "memory.h"
#include "Decoder.h"
#include "opcode_table.h"

void decoder_test(void)
{
    CPU cpu;
    
    cpu_init(&cpu);
 
    opcode_table_init();

    /* Program starts at physical address 0 */
    cpu.biu.cs = 0x0000;
    cpu.biu.ip = 0x0000;

    /* Program:
       MOV AL,05
       MOV CL,03
       ADD AL,CL
       HLT
    */

    memory_write8(0x0000, 0xEB);
    memory_write8(0x0001, 0x02);

    memory_write8(0x0002, 0xB0);
    memory_write8(0x0003, 0x01);

    memory_write8(0x0004, 0xB3);
    memory_write8(0x0005, 0x02);

    // memory_write8(0x0006, 0x29);
    // memory_write8(0x0007, 0xD8);

    memory_write8(0x0006, 0xF4);

    printf("\n=== Decoder Test === \n");
    
    while(!cpu.halted)
    {
        decoder_execute(&cpu);
    }
    // Print General Pourpous Registers
    printf("\nAX = %02X %02X\n", cpu.eu.AX.byte.High,cpu.eu.AX.byte.low);
    printf("BX = %02X %02X\n", cpu.eu.BX.byte.High,cpu.eu.BX.byte.low);
    printf("CX = %02X %02X\n", cpu.eu.CX.byte.High,cpu.eu.CX.byte.low);
    printf("DX = %02X %02X\n", cpu.eu.DX.byte.High,cpu.eu.DX.byte.low);
    // printf("FLAGS = %05X\n", cpu.eu.flags);
    printf("\nCF PF AF ZF SF OF\n");
    printf(" %d  %d  %d  %d  %d  %d\n",
    (cpu.eu.flags & FLAG_CF) ? 1 : 0,
    (cpu.eu.flags & FLAG_PF) ? 1 : 0,
    (cpu.eu.flags & FLAG_AF) ? 1 : 0,
    (cpu.eu.flags & FLAG_ZF) ? 1 : 0,
    (cpu.eu.flags & FLAG_SF) ? 1 : 0,
    (cpu.eu.flags & FLAG_OF) ? 1 : 0);

   
}