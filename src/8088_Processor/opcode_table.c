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
   /*SUB r/m8,r8*/
   opcode_table[0x28]=op_sub_rm8_r8;
   /*ADD r/m16 ,r16*/
   opcode_table[0x01]=op_add_rm16_r16;
   /*SUB r/m16 ,r16*/
   opcode_table[0x29]=op_sub_rm16_r16;
   /*COMPARE r/m8 ,r8*/
   opcode_table[0x38]=op_cmp_rm8_r8;
   /*COMPARW r/m16 ,r16*/
   opcode_table[0x39]=op_cmp_rm16_r16;
   
   /*JMP*/
   opcode_table[0xEB]=op_jmp_short;
   /*JZ*/
   opcode_table[0x74]=op_jz_short;
   /*JNZ*/
   opcode_table[0x75]=op_jnz_short;
   
   /*JC*/
   opcode_table[0x72]=op_jc_short;
   /*JNC*/
   opcode_table[0x73]=op_jnc_short;

   opcode_table[0x20]=op_and_rm8_r8;
   opcode_table[0x21]=op_and_rm16_r16;

   opcode_table[0x08]=op_or_rm8_r8;
   opcode_table[0x09]=op_or_rm16_r16;

   opcode_table[0x30]=op_xor_rm8_r8;
   opcode_table[0x31]=op_xor_rm16_r16;

   opcode_table[0x40]=op_inc_r16;
   opcode_table[0x41]=op_inc_r16;
   opcode_table[0x42]=op_inc_r16;
   opcode_table[0x43]=op_inc_r16;
   opcode_table[0x44]=op_inc_r16;
   opcode_table[0x45]=op_inc_r16;
   opcode_table[0x46]=op_inc_r16;
   opcode_table[0x47]=op_inc_r16;

   opcode_table[0x48]=op_dec_r16;
   opcode_table[0x49]=op_dec_r16;
   opcode_table[0x50]=op_dec_r16;
   opcode_table[0x51]=op_dec_r16;
   opcode_table[0x52]=op_dec_r16;
   opcode_table[0x53]=op_dec_r16;
   opcode_table[0x54]=op_dec_r16;
   opcode_table[0x55]=op_dec_r16;


   /*HLT*/
   opcode_table[0xF4] = op_hlt;

}
