#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    time_t timer = time(NULL);
    printf("Time is %jd", timer);
    return 0;
}
