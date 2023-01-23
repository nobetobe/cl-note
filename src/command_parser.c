#include "command_parser.h"

struct command *parse(char *str) {
    struct command *res = malloc(sizeof(struct command));
    res->type = NUL;
    res->contents = calloc(BUFF_LEN, 1);

    if (str[0] == '-') {
        for (unsigned short i = 1; str[i] != '\0'; i++)
            res->contents[i] = str[i];
        return res;
    }

    char temp[BUFF_LEN];
    unsigned short i;
    for (i = 0; str[i] != ' '; i++) {
        temp[i] = str[i];
        temp[i+1] = '\0';
    }
    
    switch (hash(temp))
    {
    case HASH_EXIT:
        res->type = EXIT;
        break;
    
    case HASH_SECT:
        res->type = CHANGE_SECT;
        while (str[++i] != '\0')
            res->contents[i] = str[i];
        break;
    
    default:
        break;
    }
    
}