#include "list.h"
/* 初始化双向链表 */

void list_init (struct list* list) {
    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
}

/* 将链表元素elem插入元素before之前 */
void list_insert_before(struct list_elem* before,struct list_elem* elem) {
    enum intr_status old_status = intr_disable();
    before->prev->next = elem;
    elem->prev = before->prev;
    elem->next = before;
    before->prev = elem;
    intr_set_status(old_status);
}

/* 添加元素到队首。类似push操作 */
void list_push(struct list* plist,struct list_elem* elem) {
    list_insert_before(plist->head.next,elem);
}
/* 追加到队尾*/
void list_append(struct list* plist,struct list_elem* elem) {
    list_insert_before(&(plist->tail),elem);
}

/* 移除元素pelem */
void list_remove(struct list_elem* pelem) {
    enum intr_status oldstatus = intr_disable();
    pelem->prev->next  = pelem->next;
    pelem->next->prev = pelem->prev;
    intr_set_status(oldstatus);
}

/* 从链表第一个元素弹出并返回 类似pop */
struct list_elem* list_pop(struct list* plist) {
    struct list_elem* elem = plist->head.next;
    list_remove(elem);
    return elem;
}

// /* 在链表中查询obj_elem 成功时返回true 失败返回false */
// bool elem_find(struct list* plist, struct list_elem* obj_elem) {
//     struct list_elem* elem = plist->head.next;
// }
/* 从链表中查找元素obj_elem,成功时返回true,失败时返回false */
bool elem_find(struct list* plist, struct list_elem* obj_elem) {
   struct list_elem* elem = plist->head.next;
   while (elem != &plist->tail) {
      if (elem == obj_elem) {
	 return true;
      }
      elem = elem->next;
   }
   return false;
}

/* 把列表plist中的每一个元素elem和arg传给回调函数func
arg给func用来判断elem是否符合条件
本函数遍历列表中所有的元素，逐个判断是否有符合条件的元素 
找到符合条件元素返回元素指针，否则返回NULL*/
struct list_elem* list_traversal(struct list* plist,function func, int arg) {
    struct list_elem* elem  = plist->head.next;
    /* 如果队列是空 就必然没有符合条件的结点 直接返回NULL */
    if(list_empty(plist)) {
        return NULL ;
    }
    while (elem != &(plist->tail)) 
    {
        if(func(elem,arg)) {
            
            return elem;
        }
    }
    return NULL;
}
uint32_t list_len(struct list* plist) {
    struct list_elem* elem = plist->head.next;
    uint32_t length = 0;
    while (elem!= (&plist->tail)) 
    {
        length++;
        elem= elem->next;
    }
    return length;
}
//   判断链表是否为空 空返回true 不空返回false 
bool list_empty(struct list* plist) {
    return (plist->head.next==&(plist->tail)?true:false);
}
