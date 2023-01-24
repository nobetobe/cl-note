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

    if (hash(temp) == hash("exit")) {
        res->type = EXIT;
    }
    else if (hash(temp) == hash("sect")) {
        res->type = CHANGE_SECT;
        strncpy(res->contents, &str[i+1], BUFF_LEN-1);
    }
    else if (hash(temp) == hash("clear")) {
        res->type = CLEAR;
    }
    else if (hash(temp) == hash("save")) {
        res->type = SAVE;
    }
    
    return res;
}