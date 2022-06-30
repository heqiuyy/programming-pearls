#include "dlist.h"

#include <stdlib.h>

int dlist_init(dlist_head_t *p_head) {
  if (p_head == NULL) {
    return -1;
  }
  p_head->p_next = p_head;
  p_head->p_prev = p_head;
  return 0;
}

int dlist_add(dlist_head_t *p_head, dlist_node_t *p_pos, dlist_node_t *p_node) {
  if ((p_head == NULL) || (p_pos == NULL) || (p_node == NULL)) {
    return -1;
  }
  p_node->p_prev = p_pos;
  p_node->p_next = p_pos->p_next;
  p_pos->p_next->p_prev = p_node;
  p_pos->p_next = p_node;
  return 0;
}

int dlist_add_tail(dlist_head_t *p_head, dlist_node_t *p_node) {
  return dlist_add(p_head, p_head->p_prev, p_node);
}

int dlist_add_head(dlist_head_t *p_head, dlist_node_t *p_node) {
  return dlist_add(p_head, p_head, p_node);
}

int dlist_del(dlist_head_t *p_head, dlist_node_t *p_node) {
  if ((p_head == NULL) || (p_node == NULL) || (p_node == p_head)) {
    return -1;
  }
  p_node->p_prev->p_next = p_node->p_next;
  p_node->p_next->p_prev = p_node->p_prev;
  p_node->p_next = NULL;
  p_node->p_prev = NULL;
  return 0;
}

dlist_node_t *dlist_prev_get(dlist_head_t *p_head, dlist_node_t *p_pos) {
  if (p_pos != NULL) {
    return p_pos->p_prev;
  }
  return NULL;
}

dlist_node_t *dlist_next_get(dlist_head_t *p_head, dlist_node_t *p_pos) {
  if (p_pos != NULL) {
    return p_pos->p_next;
  }
  return NULL;
}

dlist_node_t *dlist_tail_get(dlist_head_t *p_head) {
  if (p_head != NULL) {
    return p_head->p_prev;
  }
  return NULL;
}

dlist_node_t *dlist_begin_get(dlist_head_t *p_head) {
  if (p_head != NULL) {
    return p_head->p_next;
  }
  return NULL;
}

dlist_node_t *dlist_end_get(dlist_head_t *p_head) {
  return p_head;
  /*
  if (p_head != NULL)
  {
      return p_head->p_prev;
  }
  return NULL;
  */
}

int dlist_foreach(dlist_head_t *p_head, dlist_node_process_t pfn_node_process,
                  void *p_arg) {
  dlist_node_t *p_tmp, *p_end;
  int ret;

  if ((p_head == NULL) || (pfn_node_process == NULL)) {
    return -1;
  }

  p_tmp = dlist_begin_get(p_head);
  p_end = dlist_end_get(p_head);

  while (p_tmp != p_end) {
    ret = pfn_node_process(p_arg, p_tmp);
    if (ret < 0) {
      return ret;
    }
    p_tmp = dlist_next_get(p_head, p_tmp);
  }
  //    pfn_node_process(p_arg, p_tmp);
  return 0;
}