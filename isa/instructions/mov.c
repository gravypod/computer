#include "cpu.h"

void set(cpu *c, const short args[])
{
    short val   = args[0];
    short reg   = args[1];

    c->registers[REG_LOCATION(reg)] = val;
}
const instruction set_instruction = {.opcode=&set, .num_args=2};


void mov(cpu *c, const short args[])
{
    short from  = args[0];
    short to    = args[1];

    c->registers[REG_LOCATION(to)] = c->registers[REG_LOCATION(from)];
}
const instruction mov_instruction = {.opcode=&mov, .num_args=2};
