#include <unistd.h>
#include <stdio.h>
#include <errno.h>


//函数很危险，容易越界，不建议使用
int main()
{
    char buf[300];
    char *p;

    p = getwd(buf);
    if(p == NULL)
    {
        perror("getwd erron!\n");
        return 0;
    }

    printf("%s\n", p);
}