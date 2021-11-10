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
#include "roapgrops.h"
#include "roapdijkstras.h"
/*Function Name: readfile
  Input: Pointer to char (name of the file to be read)
  Output: pointer to pointer to int (matrix)
  Date Created: 05 Oct 2021
  Last Revised: 13 Oct 2021
  Definition:
*/
 void readwritefile(char*_filenamein, int sflag){
	int** matrix = NULL, *st = NULL, *TotalCost=NULL, *Wallnumber=NULL;
	int readctrl = -1, readcnt = -0, result=0, i=0;
	double *wt=NULL;
	bool brkFlag = false, debug = true;
	int lines=0, colummns=0, cellline=0, cellcol=0, celldata=0, targetcellline=0, targetcellcol=0,targetcellline2=1, targetcellcol2=1;	
	char varID[2] ={'\0'};
	char* _filenameout= gen_outname(_filenamein, sflag);
	check_inname(_filenamein, sflag);
	FILE* fp = fopen(_filenamein,"r");
	FILE* fpout=fopen(_filenameout, "w");
	graph* grapho= NULL;
	node *aux=NULL, *aux2=NULL;
	if (fp == NULL)
		help(Read_Error,File_Not_Found); 
	while (feof(fp)==0){
		readctrl = -1; //reset as security method
		readcnt = 0;
		brkFlag = false;
		lines=0;
		colummns=0;
		cellline=0; 
		cellcol=0; 
		celldata=0; 
		targetcellline=0; 
		targetcellcol=0; 
		targetcellline2=1; 
		targetcellcol2=1;
		if((fscanf(fp, "%d %d %d %d", &lines, &colummns, &targetcellline, &targetcellcol)) !=4 && feof(fp)==0)
			help(Read_Error, Bad_Info);
		if(sflag ==1){
			if((fscanf(fp, "%s",varID))!=1 && feof(fp)==0)
			if(strcmp(varID,"A6")==0){ //check if variant A6 is active
				if((fscanf(fp, "%d %d", &targetcellline2, &targetcellcol2))!=2  && feof(fp)==0)
					help(Read_Error, Bad_Info);
			}
		}
		if((fscanf(fp, "%d", &readctrl)) !=1  && feof(fp)==0)
			help(Read_Error, Bad_Info);
		if((targetcellline < 1||targetcellline2 < 1||targetcellcol < 1||targetcellcol2 < 1|| targetcellline > lines ||targetcellline2 > lines || targetcellcol > colummns ||targetcellcol2 > colummns) && feof(fp)==0 && sflag==1){
			result =-2;
			brkFlag = true;
		}
		if(brkFlag==false) 
			matrix = matrixalloc(lines, colummns); //generate read matrix
		while (readcnt<readctrl){
			if((fscanf(fp, "%d %d %d", &cellline, &cellcol, &celldata)) !=3 && feof(fp)==0)
				help(Read_Error, File_Not_Found);
			if(brkFlag==false)
				cellseed(matrix, cellline, cellcol, celldata, lines, colummns);
			readcnt++;
			}
			if(feof(fp)!=0)
                                break;
			if(brkFlag==false){
				if(sflag==1)
					result=variant_test(matrix, targetcellline, targetcellcol, targetcellline2, targetcellcol2, varID, lines, colummns);
				
				else{
					if(debug==true)
						printf("target: %d %d", targetcellline, targetcellcol);
					grapho=CaBgraph(matrix,lines,colummns,targetcellline,targetcellcol, fpout); /*add filenameout*/
					st = (int*)malloc(sizeof(int)*grapho->TotalVertex);
					wt = (double*)malloc(sizeof(double)*grapho->TotalVertex);
					if(debug==true)
						printgraph(grapho);
					st=dijsktras(grapho,0,st,wt);
					Wallnumber = (int*)malloc(sizeof(int));
					TotalCost = (int*)malloc(sizeof(int));
					recurprint_spath(st,grapho,fpout,1,Wallnumber,TotalCost);

				}
			}
				if(sflag==1)
					fprintf(fpout,"%d\n\n",result);
			if(brkFlag==false){
				if(grapho==NULL)
					freematrix(matrix, lines, colummns);
				if(grapho !=NULL){
					 for (i = 0; i < (grapho->TotalVertex); i++){
        					for (aux = grapho->adjlist[i]; aux != NULL; aux = aux2){
            						aux2 = aux->next;
							free(aux);
        					}
    					}
					free(grapho->adjlist);
					free(grapho);
					free(st);
					free(wt);
					free(Wallnumber);
					free(TotalCost);
				}	
			}
		}
	if(brkFlag==false){
		if(grapho==NULL)
			freematrix(matrix,lines,colummns);
	}
	fclose(fp);
	fclose(fpout);
	free (_filenameout);

 }
//08 Oct
char* gen_outname(char* _filenamein, int sflag){
	int lenght=strlen(_filenamein);
	char* _filenameout=(char*)malloc((sizeof(char)*lenght)+2);
	strcpy(_filenameout, _filenamein);
	if(sflag==1){
		_filenameout[lenght-3]='s';
		_filenameout[lenght-2]='o';
		_filenameout[lenght-1]='l';
		_filenameout[lenght]='1';
		_filenameout[lenght+1]='\0';
	}
	else{
                _filenameout[lenght-2]='s';
                _filenameout[lenght-1]='o';
                _filenameout[lenght]='l';
                _filenameout[lenght+1]='\0';
        }
	return _filenameout;
}
//08 Oct
void check_inname(char* _filenamein,int sflag){
	int lenght=strlen(_filenamein);
	if(sflag==1){
		if(_filenamein[lenght-3]!='i' || _filenamein[lenght-2] !='n'||_filenamein[lenght-1] != '1')
			help(Read_Error, Unsupported_Extension);
	}
	else {
		if(_filenamein[lenght-2]!='i' || _filenamein[lenght-1] !='n')
                        help(Read_Error, Unsupported_Extension);
        }
}

void recurprint_spath(int* st,graph *grapho, FILE* fpout, int target, int* Wallnumber, int* Totalcost){
        int brkLine=0,brkCol=0, cost=0;
	node* aux=NULL;
        if(st[1]==-1){
                fprintf(fpout,"-1");
                return;
        }
	if(target!=0){
		(*Wallnumber)++;
	}
        if(target!=0){
                recurprint_spath(st,grapho,fpout,st[target],Wallnumber,Totalcost);
	 	for (aux = grapho->adjlist[target]; aux != NULL; aux = aux->next){
                                if((aux->vertexID==st[target])){
                                        brkLine=aux->brokenLine;
                                        brkCol=aux->brokenCol;
					cost=aux->edge_cost;
					(*Totalcost)+=aux->edge_cost;
                                }
                        }
                fprintf(fpout,"%d %d %d \n",brkLine, brkCol, cost);
	}
	if(target==0){
		fprintf(fpout,"%d\n",(*Totalcost));
		fprintf(fpout,"%d\n",(*Wallnumber));
	}
                
}
