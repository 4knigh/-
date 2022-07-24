#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    // time_t timep;
    // struct tm* p;
    // time (&timep);
    // p = gmtime(&timep);
    // printf ("%d \n", 1+p->tm_mon);

    char *value1 = "0-6";
    
    
    printf ("%d \n%d \n", strlen(value1), strcmp(value1, "0-6"));

    return 0;
}
