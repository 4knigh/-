#include "segqueue.h"
#include "dir.h"
#include "stat.h"
#include <stdio.h>

int main(int arge, char* argc[])
{
    SegQueue* list = init();
    int num = 0;
    num = init_s(argc[1], list);



    while(list->size != 0)
    {
        char* new = func(list);
        printf("%s\n",new);
        num += init_s(new, list);
        dequeue(list);
    }

    printf("%d\n", num);
    printf("%dk\n",(num/1000));
}