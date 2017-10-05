
#ifndef INSTRUCTIONS_CPU
#define INSTRUCTIONS_CPU

typedef struct {
	char pc; // Max size of memory
	char registers[256];
} cpu;

typedef struct {
	void (*opcode)(cpu *c, const char args[]);
	char num_args;
} instruction;


#endif
