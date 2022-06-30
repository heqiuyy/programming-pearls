#ifndef _ITERATOR_H
#define _ITERATOR_H

typedef void *iterator_t;
typedef void (*iterator_next_t)(iterator_t *p_iter);
typedef void (*iterator_prev_t)(iterator_t *p_iter);
typedef int (*compare_t)(iterator_t it1, iterator_t it2);
typedef void (*swap_t)(iterator_t it1, iterator_t it2);
typedef int (*visit_t)(void *p_arg, iterator_t it);

typedef struct _iterator_if {
  iterator_next_t pfn_next;  //调用迭代器后移的函数指针，相当于p1++
  iterator_prev_t pfn_prev;  //调用迭代器前移的函数指针，相当于p2--
} iterator_if_t;

void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next,
                      iterator_prev_t pfn_prev);
void iterator_next(iterator_if_t *p_if,
                   iterator_t *p_iter);  //迭代器后移函数，相当于++
void iterator_prev(iterator_if_t *p_if,
                   iterator_t *p_iter);  //迭代器前移函数，相当于--
// void iterator_if_get(iterator_if_t *p_if);
void iter_sort(iterator_if_t *p_if, iterator_t begin, iterator_t end,
               compare_t compare, swap_t swap);
void iter_foreach(iterator_if_t *p_if, iterator_t begin, iterator_t end,
                  visit_t visit, void *p_arg);
#endif