#ifndef __LIST_H
#define __LIST_H
#include "global.h"
#define offset(struct_type, member) (int)(&((struct_type *)0)->member)

// 类似反射 通过对象元素来获取对象
#define elem2enter(struct_type, struct_member_name, elem_ptr) \
    (struct_type *)((int)elem_ptr - offset(struct_type, struct_member_name))

/** 定义链表节点成员结构
* 节点中不需要数据成员，只要求前驱和后驱节点指针 */
struct list_elem
{
    struct list_elem *prev;
    struct list_elem *next;
};

/* 链表结构用来实现队列 */
struct list
{
    // 头节点
    struct list_elem head;
    //尾巴节点
    struct list_elem tail;
};
// 自定义函数类型 用于做回调函数
typedef bool(function)(struct list_elem*, int arg);
void list_init(struct list *);
void list_insert_before(struct list_elem *before, struct list_elem *elem);
void list_push(struct list *plist, struct list_elem *elem);
void list_iterate(struct list *plist);
void list_append(struct list *plist, struct list_elem *elem);
void list_remove(struct list_elem *pelem);
struct list_elem *list_pop(struct list *plist);
bool list_empty(struct list *plist);
uint32_t list_len(struct list *plist);
struct list_elem *list_traversal(struct list *plist, function func, int arg);
bool elem_find(struct list *plist, struct list_elem *obj_elem);
#endif
