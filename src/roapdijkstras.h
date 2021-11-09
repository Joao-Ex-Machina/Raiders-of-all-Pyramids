

#ifndef _ROAPDIJKSTRAS_H_
#define _ROAPDIJKSTRAS_H_

#include <limits.h>
#include <bool.h>

#define P (wt[v] + aux->edge_cost)
#define exch(A, B) {int t = A; A = B; B = t; }
#define lessPri(A, B) (key(A) > key(B))
typedef void *Item;

#endif

