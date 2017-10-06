//
// Created by gravypod on 10/5/17.
//

#ifndef ASSEMBLER_OPS_H
#define ASSEMBLER_OPS_H

#include "arguments.h"

#include <stddef.h>


struct op {
    char *name;
    int num_args;
    int args[];
};

struct op hlt  = {.name= "hlt", .num_args=0, .args={}};
struct op add  = {.name= "add", .num_args=3, .args={T_REGISTER,  T_LITERAL, T_REGISTER}};
struct op cmp  = {.name= "cmp", .num_args=3, .args={T_REGISTER, T_REGISTER, T_REGISTER}};
struct op jmp  = {.name= "jmp", .num_args=1, .args={T_REGISTER}};
struct op jmpc = {.name="jmpc", .num_args=2, .args={T_REGISTER, T_REGISTER}};
struct op mov  = {.name= "mov", .num_args=2, .args={T_REGISTER, T_REGISTER}};
struct op set  = {.name= "set", .num_args=2, .args={ T_LITERAL, T_REGISTER}};

struct op *opcodes[] = {
        &hlt, &add, &cmp, &jmp, &jmpc, &mov, &set
};
size_t num_opcoces = sizeof(opcodes) / sizeof(struct op *);

static inline int find_opcode_for(const char const *op) {
    if (op)
        for (int i = 0; i < num_opcoces; i++)
            if (strcmp(op, opcodes[i]->name) == 0)
                return i;
    return -1;
}


#endif //ASSEMBLER_OPS_H
