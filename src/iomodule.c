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
  Definition: Main read and write function. Calls needed operative function.
*/
 void readwritefile(char*_filenamein, int sflag){
	int** matrix = NULL, *st = NULL, *Wallnumber=NULL;
	int readctrl = -1, readcnt = -0, result=0, i=0;
	double *wt=NULL;
	bool brkFlag = false, debug = false, stopread =false;
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
	while (stopread == false){
		readctrl = -1; /*resets as security methods*/
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
		if((fscanf(fp, "%d %d %d %d", &lines, &colummns, &targetcellline, &targetcellcol)) !=4)
			stopread=true;
		if(stopread==true){
			brkFlag = true;
			break;
		}
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
			if(brkFlag==false){
				if(sflag==1)
					result=variant_test(matrix, targetcellline, targetcellcol, targetcellline2, targetcellcol2, varID, lines, colummns);
				
				else{
					if(debug==true)
						printf("target: %d %d", targetcellline, targetcellcol);
					grapho=CaBgraph(matrix,lines,colummns,targetcellline,targetcellcol, fpout); /*generate graph*/
					if(grapho!=NULL){
						st = (int*)malloc(sizeof(int)*grapho->TotalVertex);
						if(st==NULL)
							exit(1);
						wt = (double*)malloc(sizeof(double)*grapho->TotalVertex);
						if(wt==NULL)
							exit(1);
						if(debug==true)
							printgraph(grapho);
						st=dijsktras(grapho,0,st,wt);
						Wallnumber = (int*)malloc(sizeof(int));
						if(Wallnumber==NULL)
							exit(1);
						Wallnumber[0]=0;
						recurprint_spath(st,wt,grapho,fpout,1,Wallnumber);
					}

				}
			}
				if(sflag==1)
					fprintf(fpout,"%d\n\n",result);
			if(brkFlag==false){
				if(grapho==NULL)
					freematrix(matrix, lines, colummns);
				if(grapho !=NULL){
					 for (i = 0; i < (grapho->TotalVertex); i++){ /*free adjacency lists*/
        					for (aux = grapho->adjlist[i]; aux != NULL; aux = aux2){
            						aux2 = aux->next;
							free(aux);
        					}
    					}
					free(grapho->adjlist); /*free used blocks*/
					free(grapho);
					free(st);
					free(wt);
					free(Wallnumber);
				}	
			}
		}
	if(brkFlag==false){
		if(grapho==NULL) /*free matrix in case there was no graph produce and consequently no matrix freeing*/
			freematrix(matrix,lines,colummns);
	}
	fclose(fp); /*Ended reading close files and free ouput file name string*/
	fclose(fpout);
	free (_filenameout);

 }
/*Function Name: gen_outname
  Input: 1 string (input file name), 1 int (sflag to determine submission phase) [could have been a boolean]
  Output: string
  Date Created: 08 Oct 2021
  Last Revised: 08 Oct 2021
  Definition: Generates output file name
*/
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
/*Function Name: check_inname
  Input: 1 string (input file name), 1 int (sflag to determine submission phase) [could have been a boolean]
  Output: No output. May exit program
  Date Created: 08 Oct 2021
  Last Revised: 08 Oct 2021
  Definition: Checks if input extension is correct
*/
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
/*Function Name: recurprint_spath
  Input: Two pointer to integer (shortest path travessy and weight vectors), pointer to graph struct, File pointer, target/destination room ID (which is 1), vector for number of broken Walls [declared outside for initialization and to avoid a reset during recursion]
  Output: pointer to pointer to int (matrix)
  Date Created: 10 Nov 2021
  Last Revised: 11 Nov 2021
  Definition: Recursive print function for final phase file printing. This was needed since st[roomID1]=roomID2 from which roomID1 was reached
*/
void recurprint_spath(int* st,double* wt,graph *grapho, FILE* fpout, int target, int* Wallnumber){
        int brkLine=0,brkCol=0, cost=0;
	node* aux=NULL;
        if(st[1]==-1){  /*if the target room was never visited*/
                fprintf(fpout,"-1\n\n"); 
                return;
        }
	if(target!=0){ /*One wall per travessy between rooms, until he have reached the initial room*/
		Wallnumber[0]++;
	}
        if(target!=0){
                recurprint_spath(st,wt,grapho,fpout,st[target],Wallnumber); /*Calls until we get to initial room*/
	 	for (aux = grapho->adjlist[target]; aux != NULL; aux = aux->next){ /*find connection between room in graph*/
                                if((aux->vertexID==st[target])){
                                        brkLine=aux->brokenLine; /*Get the connection coordinates and cost*/
                                        brkCol=aux->brokenCol;
					cost=aux->edge_cost;
                                }
                        }
                fprintf(fpout,"%d %d %d \n",brkLine, brkCol, cost); /*print them*/
	}
	if(target==0){
		fprintf(fpout,"%d\n",(int)wt[1]); /*Total cost is equal to the total cost to reach destination room, given in the weight vector*/
		fprintf(fpout,"%d\n",Wallnumber[0]); /*Print nuber of Walls "demolished"*/
	}
	if(target==1)
		fprintf(fpout,"\n");/*Add separation line  between solutions*/
                
}
