//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_CREATION_H
#define ASSEMBLERCPP_CREATION_H

#include "tokens/token.h"

class LabelCreationToken : public Token {
public:
    explicit LabelCreationToken(std::string &tok) : Token(tok, T_LABEL_CREATE) {}

    void evaluate(std::map<std::string, unsigned short> &labels, unsigned short &memory_location) override {
        labels[getToken()] = memory_location;
    };

    const int memorySize() override { return 0; };
};

#endif //ASSEMBLERCPP_CREATION_H
