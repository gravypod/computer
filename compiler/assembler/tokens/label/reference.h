//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_REFERENCE_H
#define ASSEMBLERCPP_REFERENCE_H

#include "tokens/token.h"

class LabelReferenceToken : public Token {
public:
    explicit LabelReferenceToken(std::string &tok) : Token(tok, T_LABEL_USE) {}

    void evaluate(std::map<std::string, unsigned short> &labels, unsigned short &memory_location) override {
        write(labels[getToken()]);
    };
};


#endif //ASSEMBLERCPP_REFERENCE_H
