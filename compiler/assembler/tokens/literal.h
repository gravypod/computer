//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_LITERAL_H
#define ASSEMBLERCPP_LITERAL_H

#include "tokens/token.h"

class LiteralToken : public Token {
public:
    explicit LiteralToken(std::string &tok) : Token(tok, T_LITERAL) {}

    int getLiteralValue() {
        const std::string &tok = getToken();

        switch (tok[0]) {
            case 'h':
                return std::stoi(tok.substr(1), nullptr, 16);
            case 'b':
                return std::stoi(tok.substr(1), nullptr, 2);
            case '-':
                return -std::stoi(tok.substr(1), nullptr, 10);
            default:
                return std::stoi(tok, nullptr, 10);
        }
    }

    bool hasError() override {
        if (getToken().length() == 0) {
            return true;
        }
        auto val = (unsigned int) getLiteralValue();
        return val > USHRT_MAX;
    }

    void evaluate(std::map<std::string, unsigned short> &labels, unsigned short &memory_location) override {
        write((unsigned short) getLiteralValue());
    };
};


#endif //ASSEMBLERCPP_LITERAL_H
