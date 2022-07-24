#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int ret = truncate("1.c", 100);
    if(ret == -1)
    {
        perror("truncate error");
        return 1;
    }

    int fd = open("1.c", O_RDWR);
    if (fd == -1)
    {
        perror("open 1.c erron");
        return 1;
    }
    ftruncate(fd, 50);

    return 0;
}