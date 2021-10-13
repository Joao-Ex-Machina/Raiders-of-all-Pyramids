/*-----------------------------------------------------------------------------------------------------+
| roapbops.h       	 |Library for the B(asic)op(eration)s module (basicopsmodule.c), containing    |
|                        |non-pathfinding function definitions and macros used.                        |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 08 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#ifndef ROAPBOPS_H_INCLUDED
#define ROAPBOPS_H_INCLUDED

#define left 0
#define up 1
#define down 2
#define right 3
#define white 0
#define black -1
#define grey 1
#define path -2

int variant_test(int** matrix, int targetcellline, int targetcellcol, int targetcellline2, int targetcellcol2, char varID[2], int lines, int colummns);
int check_neighbours (int** matrix, int targetcelllline, int targetcellcol, int lines, int columns, int colour);
int check_breakability(int** matrix, int targetcelllline, int targetcellcol, int lines, int columns);
int* check_bounds(int targetcellline, int targetcellcol, int lines, int colummns);
int flood_room(int** matrix, int targetcellline, int targetcellcol,int targetcellline2, int targetcellcol2, int lines, int colummns, int firstflag );
#endif
