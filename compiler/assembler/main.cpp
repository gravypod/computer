#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include "instructions.h"

#include "tokens/token.h"
#include "tokens/literal.h"
#include "tokens/register.h"
#include "tokens/label/creation.h"
#include "tokens/label/reference.h"
#include "tokens/op.h"

// https://stackoverflow.com/a/1798170/1127064
std::string trim(const std::string &str,
                 const std::string &whitespace = " \n\r\t") {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


void label(std::string &line, std::vector<Token *> &tokens) {
    unsigned long colon = line.find_first_of(':');

    if (colon == std::string::npos)
        return;

    std::string label = trim(line.substr(0, colon));
    std::string rest = trim(line.substr(colon + 1));
    line = trim(rest);
    tokens.push_back(new LabelCreationToken(label));

}

void tokenize(std::string &line, std::string &op, std::vector<std::string> &args) {
    static std::string tok;

    std::istringstream iss(line);

    while (getline(iss, tok, ' ')) {
        tok = trim(tok, " \r\n\t,");

        // Skip blank tokens.
        if (tok.empty())
            continue;

        if (op.empty()) {
            op = tok;
            continue;
        }

        args.push_back(tok);
    }

}


bool arguments(std::string &op, std::vector<std::string> &args, std::vector<Token *> &tokens) {
    ins *instruction = find_instruction(op);
    for (int i = 0; i < instruction->num_args; i++) {
        std::string &arg = args[i];

        switch (instruction->types[i]) {
            case T_ARG_REGISTER:
                if (is_register(arg)) {
                    tokens.push_back(new RegisterToken(arg));
                } else {
                    std::cerr << "ERR: Not a register: " << arg << std::endl;
                    return false;
                }
                continue;
            case T_ARG_LITERAL:
                if (is_literal(arg)) {
                    tokens.push_back(new LiteralToken(arg));
                } else if (is_label(arg)) {
                    std::string label_name = trim(arg.substr(1, arg.length() - 2));
                    tokens.push_back(new LabelReferenceToken(label_name));
                } else {
                    std::cerr << "ERR: Not a literal" << std::endl;
                    return false;
                }
                continue;
        }
    }
    return true;
}


int assemble(std::istream &in, std::vector<Token *> &tokens) {
    std::string line;

    while (getline(in, line)) {
        line = trim(line);

        // Handle and label creation
        label(line, tokens);

        if (line.empty())
            continue;


        // TODO: Standard library includes
        // Comment line
        if (line[0] == '#')
            continue;
        // File includes: Local directory
        if (line[0] == '!') {
            std::ifstream file(line.substr(1));
            if (!file.good()) {
                std::cout << "ERR: Failed to include file " << line.substr(1) << std::endl;
                return 1;
            }
            int status = assemble(file, tokens);
            if (status)
                return status;
            continue;
        }

        std::string op;
        std::vector<std::string> args;

        // Tokenize string
        tokenize(line, op, args);

        tokens.push_back(new OpNameToken(op));

        if (!arguments(op, args, tokens))
            return 1;
    }


    return 0;
}


int main() {
    std::vector<Token *> tokens;

    //std::ifstream in("test.asm");
    int status = assemble(std::cin, tokens); // std::cin);

    if (status)
        return status;

    // Define our labels
    std::map<std::string, unsigned short> labels;
    unsigned short memory_location;

    // Define all locations of labels
    memory_location = 0;
    for (auto &token : tokens) {
        if (token->getType() == T_LABEL_CREATE) {
            token->evaluate(labels, memory_location);
        }
        memory_location += token->memorySize();
    }

    // Look for errors and find locations
    memory_location = 0;
    for (auto &token : tokens) {

        if (token->getType() == T_LABEL_USE && labels.count(token->getToken()) == 0) {
            std::cerr << "ERR: Undefined label '" << token->getToken() << "' used." << std::endl;
            return 1;
        }
        if (token->hasError()) { // TODO look for undeclared labels
            std::cerr << "ERR: TODO '" << token->getToken() << "' has error" << std::endl;
            return 1;
        }
        memory_location += token->memorySize();
    }

    // Evaluate all of our code
    memory_location = 0;
    for (auto &token : tokens) {
        if (token->getType() == T_LABEL_CREATE) {
            continue;
        }
        token->evaluate(labels, memory_location);
        memory_location += token->memorySize();
    }

}