/*-----------------------------------------------------------------------------------------------------+
| roapdikjstras.h      	 |Final phase Dijkstras MST algorithm and queue based functions declaration    |
|                        |and dependencies for dikjstrasmodule.c                                       |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 09 November 2021                                                                               |
+-----------------------------------------------------------------------------------------------------*/

#ifndef _ROAPDIJKSTRAS_H_
#define _ROAPDIJKSTRAS_H_

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define P (wt[v] + aux->edge_cost)
#define exch(A, B) {int t = A; A = B; B = t; }
typedef struct graph graph;
void HPQinit(unsigned Size);
void HPQinsert(int v);
int* dijsktras(graph *grapho, int s, int *st, double *wt);
void FixDown(int Idx, int N, double *wt);
void FixUp(int Idx, double* wt);
bool lessPri(int A, int B,  double* wt);
int HPQdelmin(double *wt);
bool HPQEmpty();
#endif

