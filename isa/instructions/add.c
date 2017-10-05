#include "add.h"

void add(cpu *c, const char args[])
{
	char left  = args[0];
	char right = args[1];
	char reg   = args[2];

	c->registers[reg] = (left + right);
}
const instruction add_instruction = {.opcode=&add, .num_args=3};

