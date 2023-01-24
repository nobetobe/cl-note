#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#include "sect.h"

// djb2 hash
unsigned long hash(unsigned char *str);

void save(struct sect *contents, FILE *file, int num_tabs);

#endif