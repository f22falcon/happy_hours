#include  "opcode_table.h"
#include   "instructions.h"

OpcodeHandler opcode_table[256];
void opcode_table_init(void)
{
   /*MOV AL,imm8*/
   opcode_table[0xB0]= op_mov_rl_imm8;

   /*MOV CL,imm8*/
   opcode_table[0xB1]= op_mov_rl_imm8;

   /*MOV DL,imm8*/
   opcode_table[0xB2]= op_mov_rl_imm8;

   /*MOV BL,imm8*/
   opcode_table[0xB3]= op_mov_rl_imm8;

   /*Mov AH,imm8*/
   opcode_table[0xB4]= op_mov_rl_imm8;

   /*MOV CH,imm8*/
   opcode_table[0xB5]= op_mov_rl_imm8;

   /*MOV DH,imm8*/
   opcode_table[0xB6]= op_mov_rl_imm8;

   /*MOV BH,imm8*/
   opcode_table[0xB7]= op_mov_rl_imm8;
   
   /*MOV AX,imm16*/
   opcode_table[0xB8]= op_mov_rl_imm16;

   /*MOV CX,imm16*/
   opcode_table[0xB9]= op_mov_rl_imm16;

   /*MOV DX,imm16*/
   opcode_table[0xBA]= op_mov_rl_imm16;

   /*MOV BX,imm16*/
   opcode_table[0xBB]= op_mov_rl_imm16;
   
   /*Mov SP,imm16*/
   opcode_table[0xBC]= op_mov_rl_imm16;

   /*MOV BP,imm16*/
   opcode_table[0xBD]= op_mov_rl_imm16;

   /*MOV SI,imm16*/
   opcode_table[0xBE]= op_mov_rl_imm16;

   /*MOV DI,imm16*/
   opcode_table[0xBF]= op_mov_rl_imm16;
   

   /*ADD r/m8 ,r8*/
   opcode_table[0x00]=op_add_rm8_r8;
   /*ADD r/m16 ,r16*/
   opcode_table[0x01]=op_add_rm16_r16;
   

   /*HLT*/
   opcode_table[0xF4] = op_hlt;

}
