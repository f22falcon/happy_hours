#include "cpu_struct.h"
#include <string.h>


void cpu_init(CPU *cpu){
    memset(cpu,0,sizeof(CPU));
}
void cpu_reset(CPU *cpu){
    memset(cpu,0,sizeof(CPU));

    /*8088 Reset State*/
    cpu->biu.cs = 0xFFFF;
    cpu->biu.ip = 0x0000;

    cpu->biu.ds = 0x000;
    cpu->biu.es = 0x000;
    cpu->biu.ss = 0x000;
    
    cpu->eu.flags= 0x0002;
    
    cpu->biu.queue_head =0;
    cpu->biu.queue_tail = 0;
    cpu->biu.queue_count = 0;

    

}