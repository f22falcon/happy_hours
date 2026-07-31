#include <stdio.h>
#include <stdint.h>
#include "memory_test.h"
#include "memory.h"

void memory_test(void){
    memory_init();
    printf("\n=== Memory Test === \n");

    // Test 8-bit write and read 
    memory_write8(0x1000,0xAB);
    uint8_t b = memory_read8(0x1000);
    if (b== 0xAB){
        printf("[PASS]8-bit Read/Write\n");
    }
    else{
          printf("[FAIL]8-bit Read/Write (0x%02X)\n",b);
    }
    //Test 16-bit write and read 
    memory_write16(0x2000,0xABCD);
    uint16_t w =memory_read16(0x2000);

    if (w== 0xABCD){
        printf("[PASS]16-bit Read/Write\n");
    }
    else{
          printf("[FAIL]16-bit Read/Write (0x%04X)\n",w);
    }
    //check little endien storage
    printf("\nLittle-endian check:\n"); 
    printf("Memory[0x2000]=0x%02X\n",memory_read8(0x2000)); 
    printf("Memory[0x2001]=0x%02X\n",memory_read8(0x2001)); 
    //Physical address claculation check
    uint32_t addr =Physical_address(0x1234,0x5678);
    printf("\nPhysical Address =  0x%05X\n",addr);
    printf("Memory module test completed.\n");
}