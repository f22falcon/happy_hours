#include <stdio.h>
#include "memory_test.h"
#include "Decoder_test.h"
#include "Biu_test.h"
#include "Decoder.h"
#include "opcode_table.h"

int main(void){
    printf("8088 Emulator IS Running ....\n");
    // memory_test ();
    // Biu_test ();
    decoder_test();
    return 0;
}