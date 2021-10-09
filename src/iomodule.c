/*-----------------------------------------------------------------------------------------------------+
| iomodule.c             |Read/Write file for roapmain.c                           		       |
|                        |Contains the main read/write function                                        |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/

#include "roapio.h"
#include "roaphelp.h"
#include "roapbops.h"
#include "roapmatrix.h"

/*Function Name: readfile
  Input: Pointer to char (name of the file to be read)
  Output: pointer to pointer to int (matrix)
  Date Created: 05 Oct 2021
  Last Revised: 09 Oct 2021
  Definition:
*/
 void readwritefile(char*_filenamein, int sflag){
	int** matrix = NULL;
	int readctrl = -1, readcnt = -0, result=0;
	int lines=0, colummns=0, cellline=0, cellcol=0, celldata=0, targetcellline=0, targetcelllcol=0,targetcellline2=0, targetcelllcol2=0;	
	char varID[2] ={'\0'};
	char* _filenameout= gen_outname(_filenamein);
	check_inname(_filenamein, sflag);
	FILE* fp = fopen(_filenamein,"r");
	FILE* fpout=fopen(_filenameout, "w");
	if (fp == NULL)
		help(Read_Error,File_Not_Found); 
	while (feof(fp)==0){
		readctrl = -1; //reset control and counter
		readcnt = 0;
			fscanf(fp, "%d %d %d %d %s", &lines, &colummns, &targetcellline, &targetcelllcol, varID);
			if(strcmp(varID,"A6")==0) //check if variant A6 is active
				fscanf(fp, "%d %d", &targetcellline2, &targetcelllcol2);
			fscanf(fp, "%d", &readctrl);
			matrix = matrixalloc(lines, colummns); //generate read matrix
			while (readcnt<readctrl){
				fscanf(fp, "%d %d %d", &cellline, &cellcol, &celldata);
				cellseed(matrix, cellline, cellcol, celldata);
				readcnt++;
			}
			result=variant_test(matrix, targetcellline, targetcelllcol, targetcellline2, targetcelllcol2, varID, lines, colummns);
                	fprintf(fpout,"%d\n\n",result);
			freematrix(matrix, lines, colummns);
			if(feof(fp)==0)
				break;
		}
	fclose(fp);
	fclose(fpout);
	free (_filenameout);

 }
//08 Oct
char* gen_outname(char* _filenamein){
	int lenght=strlen(_filenamein);
	char* _filenameout=(char*)malloc((sizeof(char)*lenght)+1);
	strcpy(_filenameout, _filenamein);
	_filenameout[lenght-3]='s';
	_filenameout[lenght-2]='o';
	_filenameout[lenght-1]='l';
	_filenameout[lenght]='1';
	return _filenameout;
}
//08 Oct
void check_inname(char* _filenamein,int sflag){
	int lenght=strlen(_filenamein);
	if(sflag==1){
		if(_filenamein[lenght-3]!='i' || _filenamein[lenght-2] !='n'||_filenamein[lenght-1] != '1')
			help(Read_Error, Unsupported_Extension);
	}
}
