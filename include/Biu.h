#pragma once
#include <stdint.h>
#include "cpu_struct.h"

void biu_init(CPU *cpu);

uint8_t biu_fetch8(CPU *cpu);
uint16_t biu_fetch16(CPU *cpu);


