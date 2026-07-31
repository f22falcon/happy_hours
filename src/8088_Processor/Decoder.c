#include <stdio.h>
#include "Decoder.h"
#include  "opcode_table.h"
#include  "Biu.h"



void decoder_execute(CPU *cpu){
    uint8_t opcode = biu_fetch8(cpu);
    /*Lookup handler*/
    OpcodeHandler handler = opcode_table[opcode];
    if(handler !=NULL){
        handler(cpu);
    }
    
    else{
        printf("Unknown opcode %02X\n",opcode);
        cpu->halted=true;
    }
}