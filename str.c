#include <stdio.h>
#include <time.h>
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

int eg(char *dWDomain, egsProfileInfo_t *Info, int offset)
{
    int sDate, eDate, continousDateJudge;
    char *dWPoint;

    dWPoint = strtok(Info->date, ";");
    sDate = atoi(dWPoint);
    dWPoint = strtok(NULL, ";");
    if (NULL == dWPoint)
    {
        offset += sprintf(offset + dWDomain, "%d", sDate);
        return 1;
    }

    offset += sprintf(offset + dWDomain, "%d", sDate);
    eDate = atoi(dWPoint);

    do
    {
        dWPoint = strtok(NULL, ";");
        if (NULL != dWPoint)
        {
            if (atoi(dWPoint) > eDate + 1)
            {
                if (eDate > sDate + 1 && continousDateJudge == 1)
                {
                    offset += sprintf(offset + dWDomain, "-%d", eDate);
                }
                else
                {
                    offset += sprintf(offset + dWDomain, ",%d", eDate);
                }
                sDate = atoi(dWPoint);
                offset += sprintf(offset + dWDomain, ",%d", sDate);
                dWPoint = strtok(NULL, ";");
                if (NULL == dWPoint)
                {
                    break;
                }
                continousDateJudge = 0;
            }
            else if (atoi(dWPoint) == eDate + 1)
            {
                continousDateJudge = 1;
            }
            eDate = atoi(dWPoint);
        }
        else
        {
            if (eDate > sDate + 1 && continousDateJudge == 1)
            {
                sprintf(offset + dWDomain, "-%d", eDate);
            }
            else
            {
                sprintf(offset + dWDomain, ",%d", eDate);
            }
        }

    } while (NULL != dWPoint);
    return 0;
}

int egs(char *timeDomain, egsProfileInfo_t *Info)
{
    int offset = 0;
    char *dWInterval;
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);

    if (NULL == Info)
    {
        return 1;
    }

    offset += sprintf(offset + timeDomain, "%s-%s ", strtok(Info->sTime, ";"), strtok(Info->eTime, ";"));

    if (Info->type == 0) //不重复
    {
        eg(timeDomain, Info, offset);
        sprintf(timeDomain, "%s %d ?",timeDomain, 1 + p->tm_mon);
    }
    else if (1 == Info->type) //每天
    {
        offset += sprintf(offset + timeDomain, "* * *");
    }
    else if (2 == Info->type) //每周
    {
        offset += sprintf(offset + timeDomain, "? * ");

        eg(dWInterval, Info, 0);

        if (strcmp(dWInterval, "0-6") == 0)
        {
            offset += sprintf(offset + timeDomain, "*");
        }
        else
        {
            offset += sprintf(offset + timeDomain, "%s", dWInterval);
        }
    }
    else if (Info->type == 3) //每月
    {
        eg(timeDomain, Info, offset);
        sprintf(timeDomain, "%s * ?", timeDomain);
    }
}

int main()
{
    egsProfileInfo_t Info;
    sprintf(Info.sTime, "14:50;");
    sprintf(Info.eTime, "20:00;");
    Info.type = 3;
    sprintf(Info.date, "1;2;4;6;10;11;12;13;14;15;20;22;25;26;27;28;29;30;31;");
    char timeDomain[1024];
    memset(timeDomain, 0, sizeof(timeDomain));

    egs(timeDomain, &Info);
    printf("%s \n", timeDomain);

    return 0;
}