//
// Created by gravypod on 10/5/17.
//

#ifndef ASSEMBLER_ARGUMENTS_H
#define ASSEMBLER_ARGUMENTS_H

#define  T_LITERAL 0
#define T_REGISTER 1

char *convert_argument(const char *c, size_t argument_type);

#endif //ASSEMBLER_ARGUMENTS_H
