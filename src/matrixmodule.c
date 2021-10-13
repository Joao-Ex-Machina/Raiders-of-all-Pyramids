/*-----------------------------------------------------------------------------------------------------+
| matrixmodule.c         |Matrix allocation, cell seeding and Matrix deallocation module for RoaPmain.c|
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          MEEC-IST                                                                                    |
| Date: 04 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#include "roapmatrix.h"
#include "roaphelp.h"
/*Function Name: matrixalloc
  Input: 2 integers (number of collumns and lines)
  Output: pointer to pointer to int
  Date Created: 04 Out 2021
  Last Revised: 05 Out 2021
  Definition: Alloc and initialize 2D matrix with the given values for colummns and lines
  Based on: https://phyweb.physics.nus.edu.sg/~phywjs/CZ1102/lecture20/tsld014.htm
*/
int** matrixalloc(int lines, int colummns){
	int** matrix = NULL;
	int aux = 0/*, aux2 =0*/;
	matrix = (int**)calloc(lines,sizeof(int*)); //alloc and init number of lines (number of pointers to pointers)
	for(aux=0; aux < lines; aux++){
		matrix[aux]=(int*)calloc(colummns,sizeof(int));
	} //alloc and init number of colummns (number of pointers)
	/*for(aux=0; aux < lines ; aux++){
		for(aux2=0; aux2<colummns; aux2++)
			matrix[aux][aux2] = 0; //initialize all matrix cells at 0 
	}*/
	return matrix;
}
/*Function Name: cellseed
  Input: Matrix (pointer to pointer to int), 3 integers (cell to update line and collumn and cell update data)
  Output: No Return. Cell Value updated on Matrix
  Date Created: 04 Oct 2021
  Last Revised: 13 Oct 2021, Added fail-safe
  Definition: Update cell values. Verbosely indicates if cell is white, grey, black or treasure
*/
 void cellseed(int**matrix, int cellline, int cellcol, int celldata, int lines, int colummns){
	lines -=1;
	colummns -=1;
	cellcol-=1; //update lines and collumns, since the matrix starts in (0,0)
	cellline-=1;
	if(cellcol<0 || cellcol > colummns || cellline <0 || cellline > lines) //fail-safe
		help(Read_Error, Bad_Info);
	matrix[cellline][cellcol]=celldata;
}
/*Function Name: freematrix
  Input: Matrix (pointer to pointer to int), 2 integers (number of lines and colummns)
  Output: No Return. Free'd matrix related blocks from Heap
  Date Created: 05 Oct 2021
  Last Revised:
  Definition: free allocated matrix completly
*/
void freematrix (int** matrix, int lines, int colummns){
	int aux = 0;
	for(aux=0; aux < lines; aux++){ 
		free(matrix[aux]);
	}
	free(matrix);
}
