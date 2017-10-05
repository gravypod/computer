#include "cpu.h"

void add(cpu *c, const char args[])
{
	char from  = args[0];
	char value = args[1];
	char to    = args[2];

	c->registers[REG_LOCATION(to)] = (c->registers[REG_LOCATION(from)] + value);
}
const instruction add_instruction = {.opcode=&add, .num_args=3};

