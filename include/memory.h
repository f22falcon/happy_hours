#pragma once
# include <stdint.h>


#define MEMORY_SIZE (1024*1024) //1 MB
extern uint8_t memory[MEMORY_SIZE];

void memory_init(void);
void memory_reset(void);

uint8_t memory_read8(uint32_t address);
uint16_t memory_read16(uint32_t address);

void memory_write8(uint32_t address,uint8_t value);
void  memory_write16(uint32_t address, uint16_t value);

uint32_t Physical_address(uint16_t segment ,uint16_t offset);




