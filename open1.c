#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argv, char *argve[])
{
    int fd1,fd2;
    char buf[500];
    fd1 = open(argve[1], O_RDONLY);
    if(fd1 == -1)
    {
        printf("open %s erron! \n",argve[1]);
    }

    fd2 = open(argve[2], O_WRONLY || O_CREAT || O_TRUNC, 0664);
    if(fd2 == -1)
    {
        printf("open %s erron! \n",argve[2]);
    }

    while (1)
    {
        int i = read(fd1, buf, 10);
        write(fd2, buf, 10);

        if(i == 0)//判断是否读取完
            break;
    }

    close (fd1);
    close (fd2);
}