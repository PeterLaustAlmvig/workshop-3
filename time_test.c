#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    if(argc == 2){
        printf("One arguments given that is \'%s\'\n", argv[1]);
    } else if(argc == 3){
        printf("Two arguments given that is \'%s\' and \'%s\'\n", argv[1], argv[2]);
    } else{
        printf("Too many or not enough arguments given!\n");
    }
    time_t timer = time(NULL);
    printf("Time is %jd\n", timer);
    return 0;
}
