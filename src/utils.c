#include "utils.h"

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void save(struct sect *contents, FILE *file, int num_tabs) {

    for (int i = 0; i < num_tabs; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "%s\n", contents->name);
    for (int i = 0; i < contents->num_notes; i++) {
        for (int j = 0; j < num_tabs; j++) {
            fprintf(file, "\t");
        }
        fprintf(file, "-%s\n", contents->notes[i]);
    }
    fprintf(file, "\n");

    for (int i = 0; i < contents->num_subsects; i++) {
        save(contents->subsects[i], file, num_tabs+1);
    }
}