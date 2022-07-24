#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argv, char* argve[])
{
    char buf[500];
    char *p;

    p = get_current_dir_name();   
    if (p == NULL)
    {
        perror("get_current_dir_name error\n");
        return -1;
    }

    printf("%s\n",p);
    free(p);

    chdir ("/mnt/f/粤嵌教学/IO/code/");

    getcwd(buf, 500);
    printf("%s\n",buf);

    int fd = open ("/mnt/f/粤嵌教学/IO/code/文件操作", O_RDONLY);
    if(fd == -1)
    {
        perror("open error\n");
        return -1;
    }
    fchdir(fd);

    getcwd(buf, 500);
    printf("%s\n",buf);

    return 0;
}