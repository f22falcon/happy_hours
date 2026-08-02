# pragma once 
# include <stdint.h>
# include <stdbool.h>

/*------------------------------------
     16 bit-Register
--------------------------------------*/
typedef union
{
    uint16_t reg;
    struct{
        uint8_t low ;
        uint8_t High;
    }byte;
}Reg16;

/*--------------------------------------
     Bus Interface Unit
----------------------------------------*/
typedef struct
{
    /*segmant Registers*/
    uint16_t cs;
    uint16_t ds;
    uint16_t ss;
    uint16_t es;
    /*Instruction Pointer*/
    uint16_t ip;
    uint8_t queue[4];
    uint8_t queue_head;
    uint8_t queue_tail;
    uint8_t queue_count;
}BIU;

/*Execution Unit*/
typedef struct{
    /*General Porpous Registers*/
    Reg16 AX;
    Reg16 BX;
    Reg16 CX;
    Reg16 DX;
    /*Pointer /Index Registers*/
    uint16_t sp;
    uint16_t bp;
    uint16_t si;
    uint16_t di;
    /*FLAGS*/
    uint16_t flags;
    /*Instruction Register*/
    uint8_t IR;

}EU;

/*------------------------------------------------
           CPU
--------------------------------------------------*/
typedef struct {
    EU eu;
    BIU biu;
    bool halted;
}CPU;

/*---------------------------------------------------
       CPU Functions
-----------------------------------------------------*/
void cpu_init(CPU *cpu);
void cpu_reset(CPU *cpu);
