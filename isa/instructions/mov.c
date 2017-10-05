#include "cpu.h"

void set(cpu *c, const char args[])
{
    char val   = args[0];
    char reg   = args[2];

    c->registers[REG_LOCATION(reg)] = val;
}
const instruction set_instruction = {.opcode=&set, .num_args=2};


void mov(cpu *c, const char args[])
{
    char from  = args[0];
    char to    = args[2];

    c->registers[REG_LOCATION(to)] = c->registers[REG_LOCATION(from)];
}
const instruction mov_instruction = {.opcode=&mov, .num_args=2};
