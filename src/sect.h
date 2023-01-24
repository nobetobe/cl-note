#ifndef SECT_H
#define SECT_H

#include <stdlib.h>
#include <string.h>

struct sect {
    char *name;
    char **notes;
    unsigned short num_notes;
    struct sect **subsects;
    unsigned short num_subsects;
    struct sect *parent;
};

void sect_add_note(char *note, struct sect *sect, unsigned buff_len);
void sect_add_subsect(struct sect *subsect, struct sect *sect);
struct sect *sect_new_sect(char *name);


#endif