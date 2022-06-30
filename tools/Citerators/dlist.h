#ifndef _DLIST_H
#define _DLIST_H

typedef struct _dlist_node {
  struct _dlist_node *p_next; /* 指向下一个结点的指针 */
  struct _dlist_node *p_prev; /* 指向上一个结点的指针 */
} dlist_node_t;

typedef dlist_node_t dlist_head_t;
typedef int (*dlist_node_process_t)(void *p_arg, dlist_node_t *p_node);

int dlist_init(dlist_head_t *p_head);
int dlist_add(dlist_head_t *p_head, dlist_node_t *p_pos, dlist_node_t *p_node);
int dlist_add_tail(dlist_head_t *p_head, dlist_node_t *p_node);
int dlist_add_head(dlist_head_t *p_head, dlist_node_t *p_node);
int dlist_del(dlist_head_t *p_head, dlist_node_t *p_node);

dlist_node_t *dlist_prev_get(dlist_head_t *p_head, dlist_node_t *p_pos);
dlist_node_t *dlist_next_get(dlist_head_t *p_head, dlist_node_t *p_pos);
dlist_node_t *dlist_tail_get(dlist_head_t *p_head);
dlist_node_t *dlist_begin_get(dlist_head_t *p_head);
dlist_node_t *dlist_end_get(dlist_head_t *p_head);
int dlist_foreach(dlist_head_t *p_head, dlist_node_process_t pfn_node_process,
                  void *p_arg);

#endif