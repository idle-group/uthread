#include "uthread.h"
struct task_struct *main_thread;     // 主线程结构体
struct list thread_ready_list;       // 就绪队列
struct list thread_all_list;         //所有任务队列
// 调用初始线程函数
// 要实现一个switch_to 函数实现线程切换  // 在汇编函数中实现
extern void switch_to(struct task_struct *cur, struct task_struct *next);
static void kernel_thread(thread_func *function, void *func_arg)
{
    function(func_arg);
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
void thread_create(struct task_struct* pthread, thread_func function, void* func_arg) {
    /* 再留出线程栈的空间 */
    pthread->self_stack -= sizeof(struct thread_stack);
    /* 正式开始初始化 */
    struct thread_stack *kthread_stack = (struct thread_stack *)pthread->self_stack;
    kthread_stack->eip = kernel_thread;
    kthread_stack->function = function;
    kthread_stack->func_arg = func_arg;
    kthread_stack->ebp = kthread_stack->ebx = kthread_stack->esi = kthread_stack->edi;
}
