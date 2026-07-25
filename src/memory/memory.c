# include "memory.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
#include <stdint.h>

uint8_t memory[MEMORY_SIZE];

void memory_init(void){
    memset (memory ,0 ,MEMORY_SIZE);

}
void memory_reset(void){
    memset (memory ,0 ,MEMORY_SIZE);
}

uint8_t memory_read8(uint32_t address){
    if (address >MEMORY_SIZE){
        fprintf(stderr,"Memory Read Error: 0x%05X\n ,address");
        exit(EXIT_FAILURE);
    }
    return memory[address & 0xFFFFF];
}
uint16_t memory_read16(uint32_t address){
    if (address >MEMORY_SIZE){
        fprintf(stderr,"Memory Read Error: 0x%05X\n ,address");
        exit(EXIT_FAILURE);
    }
    uint8_t low = memory_read8( uint32_t address);
    uint8_t high =memory_read8 (address+1);

    return uint16_t (low | (high << 8));
}

void memory_write8(uint32_t address,uint8_t value){
    if (address >MEMORY_SIZE){
        fprintf(stderr,"Memory Read Error: 0x%05X\n ,address");
        exit(EXIT_FAILURE);
    }
    memory[address]=value;
}
void memory_write16(uint32_t address,uint16_t value){
    if (address > MEMORY_SIZE){
        fprintf(stderr,"Memory Read Error: 0x%05X\n ,address");
        exit(EXIT_FAILURE);
    }
    memory_write8( uint32_t address,uint8_t ( value & 0xFF));
    memory_write8 (address+1 , uint8_t (value >> 8));

    return uint16_t (low | (high << 8));
}

uint32_t Physical_address( uint16_t segment ,uint16_t offset){
    return ((uint32_t)segment << 4)+offset ;
}
