#include <stdio.h>
#include "Biu_test.h"
#include "memory.h"
#include "cpu_struct.h"
#include "Biu.h"

void Biu_test(void)
{
    CPU cpu;

    /* Initialize */
    memory_init();
    cpu_init(&cpu);

    /* Set CS:IP */
    cpu.biu.cs = 0x1000;
    cpu.biu.ip = 0x0000;

    /* Load instructions into memory */
    memory_write8(0x10000, 0xB8);
    memory_write8(0x10001, 0x34);
    memory_write8(0x10002, 0x12);
    memory_write8(0x10003, 0x90);

    printf("===== BIU TEST =====\n\n");

    uint8_t opcode;

    opcode = biu_fetch8(&cpu);
    printf("Fetched = %02X\tIP = %04X\n", opcode, cpu.biu.ip);

    opcode = biu_fetch8(&cpu);
    printf("Fetched = %02X\tIP = %04X\n", opcode, cpu.biu.ip);

    opcode = biu_fetch8(&cpu);
    printf("Fetched = %02X\tIP = %04X\n", opcode, cpu.biu.ip);

    opcode = biu_fetch8(&cpu);
    printf("Fetched = %02X\tIP = %04X\n", opcode, cpu.biu.ip);

    
}