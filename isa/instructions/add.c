#include "cpu.h"

void add(cpu *c, const short args[])
{
	short left  = args[0];
    short right = args[1];
    short to    = args[2];

	c->registers[REG_LOCATION(to)] = (c->registers[REG_LOCATION(left)] + c->registers[REG_LOCATION(right)]);
}
const instruction add_instruction = {.opcode=&add, .num_args=3};

