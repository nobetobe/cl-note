#include "command_parser.h"

struct command *parse(char *str) {
    struct command *res = malloc(sizeof(struct command));
    res->type = NUL;
    res->contents = calloc(BUFF_LEN, 1);

    if (str[0] == '-') {
        res->type = NOTE;
        strncpy(res->contents, &str[1], BUFF_LEN-1);
        return res;
    }

    char temp[BUFF_LEN];
    unsigned short i;
    for (i = 0; str[i] != ' ' && str[i] != '\0'; i++) {
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
        strncpy(res->contents, &str[i+1], BUFF_LEN-1);
        break;
    
    case HASH_CLEAR:
        res->type = CLEAR;
        break;
    
    default:
        break;
    }
    
    return res;
}