#include <stdio.h>
#include "Decoder.h"
#include  "opcode_table.h"
#include  "Biu.h"



void decoder_execute(CPU *cpu){
    cpu->eu.IR = biu_fetch8(cpu);
    /*Lookup handler*/
    OpcodeHandler handler = opcode_table[cpu->eu.IR];
    if(handler !=NULL){
        handler(cpu);
    }
    
    else{
        printf("Unknown opcode %02X\n",cpu->eu.IR);
        cpu->halted=true;
    }
}