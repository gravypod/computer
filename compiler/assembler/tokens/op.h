//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_OP_H
#define ASSEMBLERCPP_OP_H

#include "tokens/token.h"
#include "instructions.h"

class OpNameToken : public Token {
public:
    explicit OpNameToken(std::string &tok) : Token(tok, T_OPCODE) {}

    void evaluate(std::map<std::string, unsigned char> &labels, unsigned char &memory_location) override {
        write(find_instruction(getToken())->id, true, false);
    };
};

#endif //ASSEMBLERCPP_OP_H
