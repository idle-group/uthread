#include <stdio.h>
#include "global.h"
#include "uthread.h"
void func1(void *arg);
void func2(void *arg);
int main()
{
    printf("main start\n");
    // 初始化线程库
    thread_init();
    thread_start("k_thread_a", 31, func1, "argA ");
    thread_start("k_thread_b", 31, func2, "argB ");
    while (1)
         ;
    return 0;
}

void func1(void *arg)
{
    printf("func1\n");
    char *para = arg;
    while (1)
    {
        printf("%s\n", para);
        schedule();
    }
}

void func2(void *arg)
{
    char *para = arg;
    while (1)
    {
        printf("%s\n", para);
        schedule();
    }
}