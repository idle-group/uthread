#include <stdio.h>
#include "global.h"
#include "uthread.h"
void func1(void *arg);
void func2(void *arg);
int main()
{
    int i = 0;
    printf("main start\n");
    // 初始化线程库
    thread_init();
    struct task_struct *th1 = thread_start("k_thread_a", 31, func1, "argA ");
    // 运行一会
    for (i = 0; i < 20; i++)
    {
        printf("wake_before_main\n");
        schedule();
    }
    // 在这里唤醒
    thread_unblock(th1);
    printf("wake !!!!!!!!!!\n");
    for (i = 0; i < 20; i++)
    {
        printf("wake main\n");
        schedule();
    }
    while (1)
    {
        /* code */
    };
    

    return 0;
}
// 打印a
void func1(void *arg)
{
    printf("func1 start \n");
    char *para = arg;
    int i=0;
    for (i = 0; i < 10; i++)
    {
        printf("block_before_func1\n");
        schedule();
    }
    // 会在这里阻塞
    thread_block(TASK_BLOCKED);
     for (i = 0; i < 10; i++)
    {
        printf("wake fun1\n");
        schedule();
    }
}
