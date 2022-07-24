#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    DIR* ret = NULL;
    struct dirent* retc = NULL;
    
    ret = opendir(argv[1]);
    if (ret == NULL)
    {
        perror("opendir error");
        return -1;
    }

    
    while (retc = readdir(ret) )
    {
        //printf("%s\n", retc->d_name);
        //printf("%s/%s\n",argv[1],retc->d_name);
        char filename[500];
        sprintf(filename,"%s%s",argv[1],retc->d_name);
        printf("filename: %s\n",filename);
    }

    closedir(ret);

    return 0;

}