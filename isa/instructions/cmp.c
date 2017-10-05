#include "cpu.h"

void cmp(cpu *c, const char args[])
{
    char left  = args[0];
    char right = args[1];
    char reg   = args[2];

    char lvalue = c->registers[REG_LOCATION(left)];
    char rvalue = c->registers[REG_LOCATION(right)];

    if (lvalue < rvalue)
        c->registers[REG_LOCATION(reg)] = -1; // -1 if less
    else
        c->registers[REG_LOCATION(reg)] = (char)  (lvalue > rvalue); // 0 if equal, 1 if greater than
}
const instruction cmp_instruction = {.opcode=&cmp, .num_args=3};
