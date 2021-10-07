/*-----------------------------------------------------------------------------------------------------+
| readfilemodule.c       |Read file and data insertion module for RoaPmain.c                           |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/

#include <roap.h>

/*Function Name: readfile
  Input: Pointer to char (name of the file to be read)
  Output: pointer to pointer to int (matrix)
  Date Created: 05 Oct 2021
  Last Revised:
  Definition:
  Based on: 
*/
 int** readfile(char*_filenamein){
	int** matrix = NULL;
	int readctrl = -1, readcnt = -0;
	int lines=0, colummns=0, cellline=0, cellcol=0, celldata=0, targetcellline=0, targetcelllcol=0,targetcellline2=0, targetcelllcol2=0;
	char varID[2] ={\0};
	char* datastr = NULL;
	FILE* fp = fopen(_filenamein,"r");
	if (fp == NULL)
		help(Read_Error,File_Not_Found); //TBI
	while (feof(fp)==0){
		readctrl = -1; //reset control and counter
		readcnt = 0;
			fscanf(fp, "%d %d %d %d %s", &lines, &colummns, &targetcellline, &targetcelllcol, varID);
			if(strcmp(varID,"A6")==0) //check if variant A6 is active
				fscanf(fp, "%d %d", &targetcellline2, &targetcelllcol2,);
			fscanf(fp, "%d", &readctrl)
			matrix = matrixalloc(lines, colummns); //generate read matrix
			while (readcnt<=reactrl){
				fscanf(fp, "%d %d %d", &cellline, &cellcol, &celldata);
				cellseed(matrix, cellline, cellcol, celldata);
				readcnt++;
			}
			variant_test(matrix, targetcellline, targetcelllcol, targetcellline2, targetcelllcol2); //TBF
                	freematrix(matrix, lines, colummns);
		
		}

 }
