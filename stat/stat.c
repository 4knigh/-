#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>

/**
 * @brief 判断是什么类型文件
 * 
 * @param st 需要判断的值
 */
void mode(struct stat st);

/**
 * @brief 判断有什么权限
 * 
 * @param st 需要判断的值
 */
void judge(struct stat st);



int main(int arge, char* argv[])
{
    int ret;
    struct stat buf;
    
    ret = stat(argv[1], &buf);
    if(ret == -1)
    {
        perror("stat erron");
        return -1;
    }
    mode(buf);


    int fd = open (argv[2], O_RDWR);
    if(fd == -1)
    {
        perror("open error");
        return -1;
    }
    fstat(fd, &buf);
    mode(buf);

    ret = lstat(argv[3], &buf);
    if (ret == -1)
    {
        perror ("lstat error");
        return -1;
    }
    mode(buf);

    return 0;
}

void mode(struct stat st)
{
    printf("文件大小： %ld\n",(&st)->st_size);

    if(S_ISREG(st.st_mode))
    {
        printf("是普通文件   -");
    }
    else if(S_ISDIR(st.st_mode))
    {
        printf("是目录   d");
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

    judge(st);
}

void judge(struct stat st)
{
    char* value[9] = {"S_IRUSR", "S_IWUSR", "S_IXUSR","S_IRGRP", "S_IWGRP"
                        ,  "S_IXGRP", "S_IROTH", "S_IWOTH", "S_IXOTH"};

    char* str[9] = {"user有read的权限", "user有write权限", "user有执行权限",
                     "组用户有read权限", "组用户有write权限", "组用户有执行权限",
                     "其他用户有read权限", "其他用户有write权限", "其他用户有执行权限"};

    char* strc[9] = {"user没有read的权限", "user没有write权限", "user没有执行权限",
                     "组用户没有read权限", "组用户没有write权限", "组用户没有执行权限",
                     "其他用户没有read权限", "其他用户没有write权限", "其他用户没有执行权限"};


    for(int i = 0; i < 9; i++)
    {
        if(st.st_mode & (*(int*)value[i]))
        {
            printf("%s  ",str[i]);
        }
        else
        {
            printf("%s  ",strc[i]);
        }

        if(i == 2 || i == 5)
            printf("\n");
    }

    printf("\n");
}