#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    EGS_PROFILE_REPAT_NONE = 0,    /* 不循环 */
    EGS_PROFILE_REPAT_DAILY = 1,   /* 每天 */
    EGS_PROFILE_REPAT_WEEKLY = 2,  /* 每周 */
    EGS_PROFILE_REPAT_MONTHLY = 3, /* 每月 */
    EGS_PROFILE_REPAT_TYPE_MAX
} egsProfileRepeatType_e;

typedef struct
{
    // int32_t id;
    egsProfileRepeatType_e type;
    // time_t issuingTime;                /*添加时间*/
    // char name[NAME_LEN_MAX];
    char date[100];
    char sTime[10];
    char eTime[100];
    // int32_t source;
} egsProfileInfo_t;

int main(int argc, char const *argv[])
{
    char *value = malloc(sizeof(char *));
    egsProfileInfo_t Info;
    int offset = 0;
    const char *weakvalue[7] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期天"};

    //小时和分钟
    strcpy(value, argv[1]);
    sprintf(Info.sTime, "%s", strtok(value, "-"));
    sprintf(Info.eTime, "%s", strstr(argv[1], "-") + 1);

    //日期
    if ('?' == argv[2][0]) // ？
    {
        Info.type = EGS_PROFILE_REPAT_WEEKLY;
    }
    else if (NULL != strstr(argv[2], "-")) // -
    {
        strcpy(value, argv[2]);
        int cortl1 = atoi(strtok(value, "-"));
        int cortl2 = atoi((strstr(argv[2], "-") + 1));

        while (cortl1 <= cortl2)
        {
            offset += sprintf(Info.date + offset, "%d;", cortl1);
            cortl1++;
        }
    }
    else if (NULL != strstr(argv[2], ",")) // ,
    {
        value = strtok(argv[2], ",");
        while (value != NULL)
        {
            sprintf(Info.date, "%s;", value);
            value = strtok(NULL, ",");
        }
    }
    else if ('*' == argv[2][0]) // *
    {
        offset = 0;
        for (int i = 1; i <= 31; i++)
        {
            offset += sprintf(Info.date + offset, "%d;", i);
        }
        Info.type = EGS_PROFILE_REPAT_DAILY;
    }
    else
    {
        sprintf(Info.date, "%s;", argv[2]);
    }

    //月
    if ('*' == argv[3][0])
    {
        Info.type = EGS_PROFILE_REPAT_MONTHLY;
    }
    else
    {
        Info.type = EGS_PROFILE_REPAT_NONE;
    }

    //星期
    if ('?' == argv[4][0])
    {
    }
    else if ('*' == argv[4][0])
    {
        offset = 0;
        for (int i = 0; i < 7; i++)
        {
            offset += sprintf(Info.date + offset, "%s;", weakvalue[i]);
        }
        Info.type = EGS_PROFILE_REPAT_WEEKLY;
    }
    else if (NULL != strstr(argv[4], ","))
    {
    }
    else if (NULL != strstr(argv[4], "-"))
    {
        offset = 0;
        int i = 0;
        strcpy(value, argv[4]);
        char *value1 = strtok(value, "-");
        for (; strcmp(weakvalue[i], (strstr(argv[4], "-") + 1)) != 0; i++)
        {
            if (strcmp(weakvalue[i], value1) == 0)
            {
                offset += sprintf(Info.date, "%s;", weakvalue[i]);
                break;
            }
        }

        do
        {
            i = i + 1;
            sprintf(Info.date, "%s%s;", Info.date, weakvalue[i]);
        } while (strcmp(weakvalue[i], (strstr(argv[4], "-") + 1)) != 0);
    }
    else
    {
        sprintf(Info.date, "%s;", argv[4]);
    }

    //时间
    printf("%s \n", Info.sTime);
    printf("%s \n", Info.eTime);

    //月份
    printf("%s \n", Info.date);
    printf("%d \n", Info.type);

    return 0;
}
