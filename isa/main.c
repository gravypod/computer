#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "instructions/cpu.h"

extern const instruction add_instruction;
extern const instruction cmp_instruction;
extern const instruction jmp_instruction;
extern const instruction jmpc_instruction;
extern const instruction mov_instruction;
extern const instruction set_instruction;

#define MEM_SPACE 256

long int fsize(const char *filename)
{
	struct stat st;

	if (stat(filename, &st) == 0)
		return st.st_size;

	return -1;
}


void load_program(char memory[], char *file_name)
{
	long int size = fsize(file_name);
	FILE *f;
	if (size == -1 || size > MEM_SPACE || !(f = fopen(file_name, "rb")))
	{
		printf("System err: Program file not found\n");
		exit(1);
	}

	int size_copy = (int) size;

	while (size > 0)
	{
		const size_t len = fread((void*) memory, sizeof(char), size, f);
		size -= len;
		memory += len;
	}

	printf("System inf: Program correctly loaded! (%d bytes read)\n", size_copy);
}

int main()
{
	static cpu c;
	static char args[32]; // Arbitrarily large number of arguments
	static char memory[MEM_SPACE];
	static const instruction const *opcodes[] = {
		NULL,              // 0000 0000
		&add_instruction,  // 0000 0001(from, value, to)
		&cmp_instruction,  // 0000 0002(left register, right register, to)
		&jmp_instruction,  // 0000 0003(to)
		&jmpc_instruction, // 0000 0004(to, condition register)
		&mov_instruction,  // 0000 0005(from, to)
		&set_instruction   // 0000 0006(value, to)
	};
	static const int max_opcode = sizeof(opcodes) / sizeof(const instruction const *);

	// Clear program memory
	memset(memory, 0,   MEM_SPACE);
	// Clear CPU registers;
	memset(    &c, 0, sizeof(cpu));

	load_program(memory, "program.bin");

	printf("\t\tStarting computer @ pc=%d, mem=%d\n", c.pc, memory[c.pc]);

	long long unsigned int cycles = 0;
	while (1) {
		const char opcode = memory[c.pc];

		if (opcode < 0 || opcode > max_opcode)
		{
			printf("Bad opcode @ pc=%d, mem=%d\n", c.pc, opcode);
		}
		printf("Opcode %d\n", opcode);
		// Handle HLT
		const instruction const *i = opcodes[opcode];

		if (opcode == 0)
		{
			printf("INF: Program completed! (%llu cycles)\n", cycles);
			break;
		}

		// Handle unfound instruction
		if (!i)
		{
			printf("ERR: Unfound instruction\n");
			break;
		}

		// Handle memspace
		if ((c.pc + 1 + i->num_args) >= MEM_SPACE)
		{
			printf("ERR: Instructions incorrectly formatted\n");
			break;
		}

		// Run instruction
		i->opcode(&c, memory + c.pc + 1);

		// Advance PC
		c.pc += i->num_args + 1;
		cycles += 1;
	}

	const int r_step = 8;
	for (int r_major = 0; r_major < 256; r_major += r_step) {
		for (int r_minor = 0; r_minor < r_step; r_minor++) {
			int r = r_major + r_minor;

			printf("%*s%c%d = %4d ", (r < 100) + (r < 10), "", 'r', r, c.registers[r]);
		}
		printf("\n");
	}


}
