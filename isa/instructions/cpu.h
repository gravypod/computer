
#ifndef INSTRUCTIONS_CPU
#define INSTRUCTIONS_CPU

typedef struct {
    short pc; // Max size of memory
    short registers[256];
} cpu;

typedef struct {
	void (*opcode)(cpu *c, const short args[]);
	char num_args;
} instruction;

#define REG_LOCATION(r) ((unsigned char) r)

#endif
