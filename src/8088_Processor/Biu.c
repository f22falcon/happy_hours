#include <stdint.h>
#include "Biu.h"
#include "memory.h"


void biu_init(CPU *cpu)
{
    cpu->biu.cs = 0;
    cpu->biu.ds = 0;
    cpu->biu.ss = 0;
    cpu->biu.es = 0;
    cpu->biu.ip = 0;

    cpu->biu.queue_head = 0;
    cpu->biu.queue_tail = 0;
    cpu->biu.queue_count =0; 
}

uint8_t biu_fetch8(CPU *cpu){
    uint32_t physical_address;
    uint8_t instruction;

    physical_address =Physical_address(cpu->biu.cs ,cpu->biu.ip);
    instruction = memory_read8(physical_address);
    cpu->biu.ip++;
    return instruction;


}

uint16_t biu_fetch16(CPU *cpu){
    uint8_t low ;
    uint8_t high;

    low=biu_fetch8(cpu);
    high=biu_fetch8(cpu);
     
    return (uint16_t)(low | (high << 8));

}



