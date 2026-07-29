#include <stdio.h>
#include "memory_test.h"
#include "Biu_test.h"
#include "Decoder.h"

int main(void){
    CPU cpu;
    printf("8088 Emulator IS Running ....\n");
    // memory_test ();
    // Biu_test ();
    cpu_init(cpu);
    opcode_table_init();
    while(!cpu.halted){
        decoder_execute(&cpu);
    }
    return 0;
}