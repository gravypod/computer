#include "cpu.h"

void jmp(cpu *c, const char args[])
{
    char loc   = args[0];
    // We subtract 2 from the new PC to account for the program loop.
    c->pc = c->registers[REG_LOCATION(loc)];
    c->pc -= 2;
}
const instruction jmp_instruction = {.opcode=&jmp, .num_args=1};


void jmpc(cpu *c, const char args[])
{
    char loc   = args[0];
    char reg   = args[1];


    if (c->registers[REG_LOCATION(reg)]) {
        c->pc = c->registers[REG_LOCATION(loc)];
        // Compensate for the PC manipulation in the main loop
        c->pc -= 3;
    }
}
const instruction jmpc_instruction = {.opcode=&jmpc, .num_args=2};
