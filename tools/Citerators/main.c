#include <stdio.h>

#include "dlist.h"
#include "iterator.h"

#define ITERATOR_FOREATCH_EN 1

typedef struct _dlist_int {
  dlist_node_t node;
  int data;
} dlist_int_t;

static void __dlist_iterator_next(
    iterator_t *p_iter)  //让迭代器指向容器的下一个数据
{
  *p_iter = ((dlist_node_t *)*p_iter)->p_next;
}

static void __dlist_iterator_prev(
    iterator_t *p_iter)  //让迭代器指向容器的上一个数据
{
  *p_iter = ((dlist_node_t *)*p_iter)->p_prev;
}

int list_node_process(void *p_arg, dlist_node_t *p_node) {
  printf("%d ", ((dlist_int_t *)p_node)->data);
  return 0;
}

static int __visit(void *p_arg, iterator_t it) {
  printf("%d ", ((dlist_int_t *)it)->data);
  return 0;
}

static int __compare(iterator_t it1, iterator_t it2) {
  return ((dlist_int_t *)it1)->data - ((dlist_int_t *)it2)->data;
}

static void __swap(iterator_t it1, iterator_t it2) {
  int data = ((dlist_int_t *)it2)->data;
  ((dlist_int_t *)it2)->data = ((dlist_int_t *)it1)->data;
  ((dlist_int_t *)it1)->data = data;
}

int main(void) {
  iterator_if_t iterator_if;
  dlist_head_t head;    //定义链表头结点
  dlist_int_t node[5];  //定义5个结点空间
  int i;

  dlist_init(&head);

  for (i = 0; i < 5; i++) {  //将5个结点添加至链表尾部
    node[i].data = 5 - i;    // 使值的顺序为 5~1
    dlist_add_tail(&head, &(node[i].node));
  }
  iterator_if_init(&iterator_if, __dlist_iterator_next, __dlist_iterator_prev);

  printf("\nBefore bubble sort:\n");
#if (ITERATOR_FOREATCH_EN)
  iter_foreach(&iterator_if, dlist_begin_get(&head), dlist_end_get(&head),
               __visit, NULL);
#else
  dlist_foreach(&head, list_node_process, NULL);  //打印排序前的情况
#endif

  iter_sort(&iterator_if, dlist_begin_get(&head), dlist_end_get(&head),
            __compare, __swap);

  printf("\nAfter bubble sort:\n");

#if (ITERATOR_FOREATCH_EN)
  iter_foreach(&iterator_if, dlist_begin_get(&head), dlist_end_get(&head),
               __visit, NULL);
#else
  dlist_foreach(&head, list_node_process, NULL);  //打印排序后的情况
#endif

  return 0;
}