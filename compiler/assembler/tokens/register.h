//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_REGISTER_H
#define ASSEMBLERCPP_REGISTER_H

#include "tokens/token.h"

class RegisterToken : public Token {
public:
    explicit RegisterToken(std::string &tok) : Token(tok, T_REGISTER) {}

    int getRegisterNumber() { return std::stoi(getToken().substr(1), nullptr, 10); }

    bool hasError() override {
        const std::string &tok = getToken();

        if (tok.size() < 2)
            return true;

        int val = getRegisterNumber();

        return tok[0] != 'r' || val < 0 || val > 255;
    }

    void evaluate(std::map<std::string, unsigned short> &labels, unsigned short &memory_location) override {
        write((unsigned short) getRegisterNumber());
    };
};


#endif //ASSEMBLERCPP_REGISTER_H
