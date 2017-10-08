//
// Created by gravypod on 10/8/17.
//

#ifndef ASSEMBLERCPP_TOKEN_H
#define ASSEMBLERCPP_TOKEN_H

#include <climits>
#include <cstddef>
#include <string>
#include <map>
#include <iostream>

enum TokenType {
    T_LABEL_CREATE, T_LABEL_USE, T_REGISTER, T_LITERAL, T_OPCODE
};

class Token {
private:
    std::string tok;
    TokenType type;
public:
    explicit Token(std::string &_tok, TokenType _type) : tok(_tok), type(_type) {};

    virtual void evaluate(std::map<std::string, unsigned char> &labels, unsigned char &memory_location) = 0;

    void write(unsigned char data, const bool comment=true, const bool indent=true) {
        static const char one = '1';
        static const char zero = '0';
        static char binary[CHAR_BIT + 1];

        // Clear
        memset(binary, 0, CHAR_BIT + 1);

        char mask = 1;
        for (size_t i = 1; i <= CHAR_BIT; i++) {
            binary[CHAR_BIT - i] = (data & mask) ? one : zero;
            mask <<= 1;
        }


        if (comment) {
            if (indent)
                std::cout << "\t";
            std::cout << "# " << getToken() << std::endl;
        }

        if (indent)
            std::cout << "\t";

        std::cout << std::string(binary) << std::endl;
    }


    virtual bool hasError() { return false; }

    virtual const int memorySize() { return 1; }

    const std::string &getToken() const { return tok; }

    const TokenType &getType() const { return type; }
};


#endif //ASSEMBLERCPP_TOKEN_H
