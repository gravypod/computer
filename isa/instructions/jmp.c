#include "cpu.h"

void jmp(cpu *c, const char args[])
{
    char loc   = args[0];
    loc -= 2; // (num_args + opcode) Account for main loop.
    c->pc = loc;
}
const instruction jmp_instruction = {.opcode=&jmp, .num_args=1};


void jmpc(cpu *c, const char args[])
{
    char loc   = args[0];
    char reg   = args[1];

    loc -= 3; // (num_args + opcode) Account for main loop.

    if (c->registers[REG_LOCATION(reg)])
        c->pc = loc;
}
const instruction jmpc_instruction = {.opcode=&jmpc, .num_args=2};
