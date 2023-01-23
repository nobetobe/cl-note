#include "sect.h"

void sect_add_note(char *note, struct sect *sect) {
    sect->notes = realloc(sect->notes, sizeof(char*) * (++sect->num_notes));
    sect->notes[sect->num_notes-1] = note;
}

void sect_add_subsect(struct sect *subsect, struct sect *sect) {
    sect->subsects = realloc(sect->subsects, sizeof(char*) * (++sect->num_subsects));
    sect->subsects[sect->num_subsects-1] = subsect;
    subsect->parent = sect;
}

struct sect *sect_new_sect(char *name) {
    struct sect *newsect = malloc(sizeof(struct sect));
    newsect->name = calloc(strlen(name)+1, 1);
    strcpy(newsect->name, name);
    newsect->num_notes = 0;
    newsect->notes = malloc(0);
    newsect->num_subsects = 0;
    newsect->subsects = malloc(0);
    newsect->parent = NULL;
    return newsect;
}
