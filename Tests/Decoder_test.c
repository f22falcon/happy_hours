#include <stdio.h>

#include "Decoder_test.h"

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
       MOV BL,03
       ADD AL,BL
       HLT
    */

    memory_write8(0x0000, 0xB0);
    memory_write8(0x0001, 0x05);

    memory_write8(0x0002, 0xB3);
    memory_write8(0x0003, 0x03);

    memory_write8(0x0004, 0x00);
    memory_write8(0x0005, 0xD8);

    memory_write8(0x0006, 0xF4);

    printf("\n=== Decoder Test === \n");
    
    while(!cpu.halted)
    {
        decoder_execute(&cpu);
    }

    printf("AL = %02X\n", cpu.eu.AX.byte.low);
    printf("BL = %02X\n", cpu.eu.BX.byte.low);
    printf("FLAGS = %04X\n", cpu.eu.flags);

    if(cpu.eu.AX.byte.low == 0x08)
    {
        printf("\n[PASS] Decoder Test\n");
    }
    else
    {
        printf("\n[FAIL] Decoder Test\n");
    }
}