#include "iterator.h"

void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next,
                      iterator_prev_t pfn_prev) {
  p_if->pfn_next = pfn_next;
  p_if->pfn_prev = pfn_prev;
}

void iterator_next(iterator_if_t *p_if, iterator_t *p_iter) {
  p_if->pfn_next(p_iter);
}

void iterator_prev(iterator_if_t *p_if, iterator_t *p_iter) {
  p_if->pfn_prev(p_iter);
}

/**
 * @breif 冒泡排序算法函数
 */
void iter_sort(iterator_if_t *p_if, iterator_t begin, iterator_t end,
               compare_t compare, swap_t swap) {
  int flag = 1;            // flag = 1，表示指针的内容未交换
  iterator_t it1 = begin;  // it1指向需要排序的首元素
  iterator_t it2 = end;    // it2指向需要排序的最后一个元素之后

  iterator_t it_next;
  if (begin == end) {
    return;
  }

  while (it2 != begin) {
    it1 = begin;
    flag = 1;
    while (it1 != it2) {
      it_next = it1;                  //暂存
      iterator_next(p_if, &it_next);  // it_next为it1的下一个元素
      if (it_next == it2) break;
      if (compare(it1, it_next) > 0) {
        swap(it1, it_next);  //交换内容
        flag = 0;            // flag = 0，表示指针的内容已交换
      }
      it1 = it_next;  // it1的下一个元素
    }
    if (flag) return;  //没有交换，表示已经有序，则直接返回
    iterator_prev(p_if, &it2);  // it2向前移
  }
}

void iter_foreach(iterator_if_t *p_if, iterator_t begin, iterator_t end,
                  visit_t visit, void *p_arg) {
  iterator_t it = begin;
  while (it != end) {
    if (visit(p_arg, it) < 0) {  //若返回值为负值，表示用户终止了遍历
      return;
    }
    iterator_next(p_if, &it);  //让迭代器向后移动
  }
}