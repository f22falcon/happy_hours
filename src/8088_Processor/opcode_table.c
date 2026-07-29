#include  "opcode_table.h"
#include   "instructions.h"

void opcode_table_init(void)
{
   /*MOV AL,imm8*/
   opcode_table[0xB0]= op_mov_al_imm8;

   /*MOV BL,imm8*/
   opcode_table[0xB3]= op_mov_bl_imm8;

   /*ADD r/m8 ,r8*/
   opcode_table[0x00]=op_add_rm8_r8;

   /*HLT*/
   opcode_table[0xF4] = op_hlt;

}
