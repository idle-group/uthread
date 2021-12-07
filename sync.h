#ifndef __SYNC_H
#define __SYNC_H
#include "global.h"
#include "list.h"
// 创建一个信号量
struct semaphore {
    uint8_t value;
    struct list waiters;    //在该信号上阻塞的所有线程
};
#endif