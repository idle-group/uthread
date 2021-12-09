#ifndef __UTHREAD_H
#define __UTHREAD_H
#include "global.h"
#include "list.h"
typedef void thread_func(void *);
/* 进程或者线程的状态 */
enum task_status
{
    TASK_RUNNING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_WAITING,
    TASK_HANGING,
    TASK_DIED
};
/* 线程栈 thread_stack */
/* 线程自己的栈，用于储存线程中待执行的函数 
用于在switch_to时保存线程的运行环境
实际位置取决于实际运行情况*/

//ebp,esp,ebx,edi,esi,eip 
struct thread_stack
{
    // esp 用task_struct保存
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edi;
    uint32_t esi;
    void (*eip)(thread_func *func, void* func_arg); // 运行的函数地址
    /* 第一次上cpu时被调用 */
    /* 参数unused_ret只为占位置充数为返回地址 */
    void(*unused_retaddr);  // 如果线程结束了会调用到这个地址 // 在这里做占位置用 
    thread_func *function; // 函数名
    void *func_arg;        // 函数所需的参数
};


// 线程结构体
struct task_struct 
{
    uint32_t* self_stack; // 各线程有自己的栈 // 就是esp
    enum task_status status;
    char name[16];
    // 先做非抢占式
    // uint8_t priority; //线程优先级
    // uint8_t ticks;      // 在处理器上执行的时间滴答数
    uint32_t elapsed_ticks; // 上cpu后运行了多久 目前没有什么用
    struct list_elem general_tag; // 线程在一般队列中的结点 在调度器中相当于pcb
    struct list_elem all_list_tag; // 在线程队列thread_all_list中的结点
    uint8_t exit_status;    // 线程的退出状态
    uint32_t stack_magic; // 用这串数字做栈的边界标记,用于检测栈的溢出
};
extern struct list thread_ready_list;   //就绪线程队列
extern struct list thread_all_list;     //所有线程队列

// 获取当前正在运行的线程
struct task_struct *running_thread(void);
// 创建线程
void thread_create(struct task_struct* pthread, thread_func function, void* func_arg);
// 初始化线程
void init_thread(struct task_struct* pthread, char* name, int prio);
// 线程开始
struct task_struct* thread_start(char* name, int prio, thread_func function, void* func_arg);
// 线程初始化
void thread_init(void);
// 调度器 
void schedule(void);
// 退出当前线程
void thread_exit(struct task_struct* thread_over, bool need_schedule); 
// 线程block
// 将线程阻塞到指定状态
void thread_block(enum task_status stat);
// 线程unblock
// 将线程重新调度出来
void thread_unblock(struct task_struct* pthread);
#endif