#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argv, char* argve[])
{
    int fd, r;
    fd = open(argve[1], O_RDONLY);

    if(fd == -1)
    {
        printf("open %s erron!!\n",argve[1]);
        printf("errno = %d\n",errno);

        return -1;
    }

    char *str = "dvvkjvaldkaksakd";
    r = write(fd, str, 10);
    if (r == -1)
    {
        perror("write error: ");
    }

    r = lseek(fd, 0, SEEK_SET);
    if (r == -1)
    {
        printf("lseek error:");
    }
    
    char buf[500];
    r = read(fd, buf, 400);
    if (r > 0)
    {
        buf[r] = '\0';
        printf("%s\n",buf);
    }

    printf("fd = %d\n",fd);

    close(fd);
}