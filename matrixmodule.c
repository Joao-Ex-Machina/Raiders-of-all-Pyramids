/*-----------------------------------------------------------------------------------------------------+
| matrixmodule.c         |Matrix allocation and cell seeding module for RoaPmain.c                     |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          MEEC-IST                                                                                    |
| Date: 04 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/

#include <roap.h>
/*Function Name: matrixalloc
  Input: 2 integers (number of collumns and lines)
  Output: pointer to pointer to int
  Date Created: 04 Out 2021
  Last Revised: 
  Definition: Alloc and initialize 2D matrix with the given values for colummns and lines
*/
int** matrixalloc(int colummns, int lines){
	int** matrix = NULL;
	int aux = 0;
	matrix = (int**)calloc(lines,sizeof(int)); //alloc and init number of lines (number of pointers to pointers)
	for(aux=0; aux < lines; aux++)
		matrix[aux]=(int*)calloc(colummns,sizeof(int)); //alloc and init number of colummns (number of pointers)
	return matrix;
}
/*Function Name: cellseed
  Input: Matrix (pointer to pointer to int), 3 integers (cell to update line and collumn and cell update data)
  Output: No Return. Cell Value updated on Matrix
  Date Created: 04 Out 2021
  Last Revised: 
  Definition: Update cell values. Verbosely indicates if cell is white, grey, black or treasure
*/
 void cellseed(int**matrix, int cellcol, int cellline, int celldata){
	cellcol-=1; //update lines and collumns, since the matrix starts in (0,0)
	cellline-=1;
	matrix[cellline][cellcol]=celldata;
}


