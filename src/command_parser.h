#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdlib.h>
#include "utils.h"

#define BUFF_LEN 4096U

#define HASH_EXIT 2090237503UL
#define HASH_SECT 2090719732UL

enum COMMAND_TYPE {
    NUL = 0,
    NOTE,
    CHANGE_SECT,
    EXIT,
};

struct command {
    enum COMMAND_TYPE type;
    char* contents;
};

struct command *parse(char *str);


#endif