#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>
#include "segqueue.h"
#include "dir.h"
#include "stat.h"

int init_s(char* value, SegQueue* list)
{
    int ret, s = 0, i = 0;
    struct stat buf;
    char* str = value;

    ret = stat(value, &buf);
    if(ret == -1)
    {
        perror("stat error");
        return -1;
    }

    s += (&buf)->st_size;
    i = jude(buf);
    if(i)
    {
        char retc[500];
        sprintf(retc, "%s%c" ,str,'/');
        dir(retc, list);
    }
   
    return s;
}

int jude(struct stat st)
{
    if(S_ISREG(st.st_mode))
    {
        printf("是普通文件   -");
    }
    else if(S_ISDIR(st.st_mode))
    {
        printf("是目录   d");
        printf("\n");
        return 1;
    }
    else if(S_ISCHR(st.st_mode))
    {
        printf("是字符设备   c");
    }
    else if(S_ISBLK(st.st_mode))
    {
        printf("是块设备   b");
    }
    else if(S_ISFIFO(st.st_mode))
    {
        printf("是管道文件   p");
    }
    else if(S_ISLNK(st.st_mode))
    {
        printf("是符号链接文件   l");
    }
    else if(S_ISSOCK(st.st_mode))
    {
        printf("是套接字文件   s");
    }
    printf("\n");
    return 0;
}