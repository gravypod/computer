//
// Created by gravypod on 10/7/17.
//

#ifndef ASSEMBLERCPP_INSTRUCTIONS_H
#define ASSEMBLERCPP_INSTRUCTIONS_H

#include <array>

#define MAX_NUM_ARGS 32

enum ArgType {
    T_ARG_LITERAL,
    T_ARG_REGISTER
};

typedef struct {
    std::string name;
    unsigned char id;
    int num_args;
    std::array<ArgType, MAX_NUM_ARGS> types;
} ins;

const int num_instructions = 7;
ins instructions[] = {
        {.name="hlt", .id=0, .num_args=0, .types={}},
        {.name="add", .id=1, .num_args=3, .types={T_ARG_REGISTER, T_ARG_REGISTER, T_ARG_REGISTER}},
        {.name="cmp", .id=2, .num_args=3, .types={T_ARG_REGISTER, T_ARG_REGISTER, T_ARG_REGISTER}},
        {.name="jmp", .id=3, .num_args=1, .types={T_ARG_REGISTER}},
        {.name="jmpc", .id=4, .num_args=2, .types={T_ARG_REGISTER, T_ARG_REGISTER}},
        {.name="mov", .id=5, .num_args=2, .types={T_ARG_REGISTER, T_ARG_REGISTER}},
        {.name="set", .id=6, .num_args=2, .types={T_ARG_LITERAL, T_ARG_REGISTER}},
};

static inline bool is_real_instruction_name(std::string &s) {
    for (int i = 0; i < num_instructions; i++) {
        if (instructions[i].name == s)
            return true;
    }
    return false;
}

static inline ins *find_instruction(const std::string &name) {
    for (int i = 0; i < num_instructions; i++) {
        if (instructions[i].name == name)
            return &instructions[i];
    }
    return nullptr;
}

static inline bool is_register(const std::string &s) {
    for (int i = 1; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return s[0] == 'r';
}

static inline bool is_label(const std::string &s) {
    return s[0] == '[' && s[s.length() - 1] == ']';
}

static inline bool is_literal(const std::string &s) {
    for (int i = 1; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return s[0] == 'h' || s[0] == 'b' || s[0] == '-' || isdigit(s[0]);
}


#endif //ASSEMBLERCPP_INSTRUCTIONS_H
