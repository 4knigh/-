#include "segqueue.h"
#include "dir.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void dir(char* value, SegQueue* list)
{
    DIR* st;
    struct dirent* str = NULL;

    st = opendir(value);
    if(st == NULL)
    {
        perror("opendir st error");
    }

    while(str = readdir(st))
    {
        if(!strcmp(str->d_name, ".") || !strcmp(str->d_name, ".."))
        {
            continue;
        }
        else
        {
            char* new = str->d_name;
            char* new_node = value;
            char ret[500];
            sprintf(ret, "%s%s" ,new_node,new);

            enqueue(list, ret);
        }
    }

    closedir(st);

}