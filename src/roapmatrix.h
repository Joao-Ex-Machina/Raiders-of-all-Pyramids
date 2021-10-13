/*-----------------------------------------------------------------------------------------------------+
| roapmatrix.h           |Function Definitions for matrixmodule.c                                      |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#ifndef ROAPMATRIX_H_INCLUDED
#define ROAPMATRIX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
int** matrixalloc(int lines, int colummns);
void cellseed(int**matrix, int cellline, int cellcol, int celldata, int lines, int colummns);
void freematrix (int** matrix, int lines, int colummns);
#endif
