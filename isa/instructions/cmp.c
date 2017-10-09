#include "cpu.h"

void cmp(cpu *c, const short args[])
{
    short left  = args[0];
    short right = args[1];
    short reg   = args[2];

    short lvalue = c->registers[REG_LOCATION(left)];
    short rvalue = c->registers[REG_LOCATION(right)];

    if (lvalue < rvalue)
        c->registers[REG_LOCATION(reg)] = -1; // -1 if less
    else
        c->registers[REG_LOCATION(reg)] = (char)  (lvalue > rvalue); // 0 if equal, 1 if greater than
}
const instruction cmp_instruction = {.opcode=&cmp, .num_args=3};
