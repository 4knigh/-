#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    char buf[400];
    char *p;

    //空间要足够长
    p = getcwd(buf,400);
    if(p == NULL)
    {
        perror("getcwd erron!\n");
        return 0;
    }

    printf("%s\n",p);
}