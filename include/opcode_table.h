#ifndef OPCODE_TABLE_H
#define OPCODE_TABLE_H

#include "cpu_struct.h"

typedef void  (*OpcodeHandler)(CPU *cpu);
extern OpcodeHandler opcode_table[256];
void opcode_table_init(void);
#endif


