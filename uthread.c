#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "uthread.h"
#include "string.h"
struct task_struct *main_thread;     // 主线程结构体
struct list thread_ready_list;       // 就绪队列
struct list thread_all_list;         //所有任务队列
static struct list_elem *thread_tag; // 用于保存队列中的线程结点
struct task_struct *cur_thread;      // 全局变量当前正在运行的线程
// 调用初始线程函数

// 要实现一个switch_to 函数实现线程切换  // 在汇编函数中实现
extern void switch_to(struct task_struct *cur, struct task_struct *next);
//静态函数创建在内部
static void make_main_thread(void);
static void kernel_thread(thread_func *function, void *func_arg);

static void kernel_thread(thread_func *function, void *func_arg)
{
    function(func_arg);
    // 结束会回到这个位置 在这里可以摧毁当前线程
    printf("thread_destory\n");
    thread_exit(running_thread(), true);
}
// 获取当前正在运行的线程结构体指针
struct task_struct *running_thread()
{
    return cur_thread;
}

// 初始化线程
void init_thread(struct task_struct *pthread, char *name, int prio)
{
    // 将线程信息表清零
    memset(pthread, 0, sizeof(*pthread));
    strcpy(pthread->name, name);
    if (pthread == main_thread)
    {
        pthread->status = TASK_RUNNING;
    }
    else
    {
        pthread->status = TASK_READY;
    }
    pthread->status = TASK_RUNNING;
    /*self_kstack 是线程自己在内核态下使用的栈顶地址 */
    //在线程创建之初初始化到了该页的顶端
    pthread->self_stack = (uint32_t *)((uint32_t)pthread + PG_SIZE);
    //pthread->priority = prio;
    //pthread->ticks = prio;
    pthread->elapsed_ticks = 0;
    pthread->stack_magic = 0x20001221;
}

// 创建线程
void thread_create(struct task_struct *pthread, thread_func function, void *func_arg)
{
    /* 再留出线程栈的空间 */
    pthread->self_stack -= sizeof(struct thread_stack);
    /* 正式开始初始化 */
    struct thread_stack *kthread_stack = (struct thread_stack *)pthread->self_stack;
    kthread_stack->eip = kernel_thread;
    kthread_stack->function = function;
    kthread_stack->func_arg = func_arg;
    kthread_stack->ebp = kthread_stack->ebx = kthread_stack->esi = kthread_stack->edi;
}

// 开始线程
struct task_struct *thread_start(char *name, int prio, thread_func function, void *func_arg)
{
    // 创建线程信息表指针指针   //给他分配一个页的大小
    struct task_struct *thread = malloc(PG_SIZE);
    //初始化刚刚创建的pcb
    init_thread(thread, name, prio);
    //将要执行的函数和参数放到thread_stack中响应的位置
    thread_create(thread, function, func_arg);
    // 确保之前不在队列中
    assert(!elem_find(&thread_ready_list, &thread->general_tag));

    //  加入就绪队列
    list_append(&thread_ready_list, &thread->general_tag);
    // 确保不在全部队列中
    assert(!elem_find(&thread_all_list, &thread->all_list_tag));

    list_append(&thread_all_list, &thread->all_list_tag);
    return thread;
}

/* 将main函数线程也就是主线程完善结构体 */
static void make_main_thread(void)
{
    cur_thread = malloc(PG_SIZE); // 给主线程分配一块地址用于存线程结构体
    main_thread = running_thread();
    init_thread(main_thread, "main", 31);
    // main 函数是当前线程 不在thread_ready_list中
    assert(!elem_find(&thread_all_list, &main_thread->all_list_tag));

    list_append(&thread_all_list, &main_thread->all_list_tag);
}
// 线程库初始化
void thread_init(void)
{
    printf("thread_init start\n");
    list_init(&thread_ready_list);
    list_init(&thread_all_list);
    // 为main函数创建线程
    make_main_thread();
    printf("thread_init done\n");
}
// 调度器 调用此函数之后进行一次线程调度
void schedule()
{
    // 获取当前正在运行的线程
    struct task_struct *cur = running_thread();
    if (cur->status == TASK_RUNNING) // 当前线程正在运行才能利用调度器加入准备队列
    {
        // 添加进就绪队列尾部
        list_append(&thread_ready_list, &cur->general_tag);
        // 修改线程状态
        cur->status = TASK_READY;
    }

    // 改变线程走向
    thread_tag = NULL; // thread_tag清空
                       /* 将thread_ready_list队列中的第一个就绪线程弹出,准备将其调度上cpu. */
    // 从就绪队列中取出一个
    thread_tag = list_pop(&thread_ready_list);
    // 获取首地址
    struct task_struct *next = elem2enter(struct task_struct, general_tag, thread_tag);
    // 修改状态
    next->status = TASK_RUNNING;

    //更改储存的cur
    cur_thread = next;
    switch_to(cur, next);
}
// 退出线程 回收线程需要的资源 改变线程的状态
// 将其退出调度队列
void thread_exit(struct task_struct *thread_over, bool need_schedule)
{
    printf("thread_exit_start\n");
    // 改变线程的状态
    thread_over->status = TASK_DIED; //线程死亡
    // 将其从调度队列中移除
    list_remove(&thread_over->general_tag);
    // 将其从总线程队列中移除 //释放线程结构体在其他线程中进行
    list_remove(&thread_over->all_list_tag);
    //printf("thread_exit_over\n");

    // 进行最后一次调度 // 此处不能采用调度器
    thread_tag = NULL; // thread_tag清空
    /* 将thread_ready_list队列中的第一个就绪线程弹出,准备将其调度上cpu. */
    // 从就绪队列中取出一个
    thread_tag = list_pop(&thread_ready_list);
    // 获取首地址
    struct task_struct *next = elem2enter(struct task_struct, general_tag, thread_tag);
    // 修改状态
    next->status = TASK_RUNNING;
    //更改储存的cur
    cur_thread = next;
    switch_to(thread_over, next);
}