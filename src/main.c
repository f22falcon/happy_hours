#include <stdio.h>
#include "memory_test.h"
#include "Biu_test.h"

int main(void){
    printf("8088 Emulator IS Running ....\n");
    memory_test ();
    Biu_test ();
    return 0;
}