#ifndef STAT_H
#define STAT_H

#include <sys/stat.h>

int init_s(char* value, SegQueue* list);

int jude(struct stat st);


#endif