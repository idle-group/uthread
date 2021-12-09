#ifndef __SYNC_H
#define __SYNC_H
#include "global.h"
#include "list.h"
// 创建信号量数据结构
struct sync {
    // 信号量
    uint8_t  sync;
    // 在这个信号量上等待的线程
    struct list wait_list;
};

#endif