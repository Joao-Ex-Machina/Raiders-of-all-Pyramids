/*-----------------------------------------------------------------------------------------------------+
| graphopsmodule.c       |Final phase matrix to graph port operation and operations over graphs        |
|                        |module for roapmain.c                                                        |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 November 2021                                                                               |
+-----------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "roapgrops.h"
#include "roapbops.h"
node* CaIoUnode (int vertexID, int edge_cost, int brokenCol, int brokenLine,  node* target){
	node* new = target, *aux=NULL;
	bool eflag= false;
        if(target!= NULL){
                for(aux=target;aux->next != NULL; aux=aux->next){
			if(aux->vertexID == vertexID){
				eflag=true;
				break;
			}

		}
		if(eflag==false){
			new = (node*)malloc(sizeof(node));
			aux->next=new;
		}
        }
        else{ /*initialize node*/
		new = (node*)malloc(sizeof(node));
                new->vertexID = vertexID;
                new->next=NULL;
                new->edge_cost=edge_cost;
		new->brokenCol=brokenCol;
                new->brokenLine=brokenLine;
                return new;
        }
	if(eflag==false){
        	new->vertexID = vertexID;
        	new->next=NULL;
        	new->edge_cost=edge_cost;
		new->brokenCol=brokenCol;
                new->brokenLine=brokenLine;
	}
	else{
		if(edge_cost< aux->edge_cost){
			aux->edge_cost= edge_cost;
			aux->brokenCol=brokenCol;
			aux->brokenLine=brokenLine;
		}
	}
        return target;
}

graph* CaBgraph(int **matrix, int lines, int colummns, int targetcellline, int targetcellcol){  /*Create and Build Graph*/
	graph* grapho = (graph*)malloc(sizeof(graph));
	int i=0, j=0, dummyresult=0, colour =-4, vertex=0;
	/*Start with flooding both start and end room, as they need to be fixed colours*/
	lines-=1;
	colummns-=1;
	targetcellline-=1;
	targetcellcol-=1;
	dummyresult=flood_room(matrix,0,0,0,0,lines, colummns,start,1,1);
	vertex+=2;
	printf("target: %d %d", targetcellline, targetcellcol);
	 if(targetcellline<0 || targetcellline> lines || targetcellcol<0 || targetcellcol>colummns){
                printf("fora da matriz"); //pass to file
                exit(0);
        }
	if(matrix[targetcellline][targetcellcol]==start){
		printf("Eram da mesma sala Omega kekers!"); //pass to file
		exit(0);
	}
	dummyresult=flood_room(matrix, targetcellline, targetcellcol,0,0, lines, colummns, end,1,1);
	for (i=0; i< lines; i++){
		for(j=0; j< colummns; j++){
			if(matrix[i][j]==0){
				dummyresult=flood_room(matrix,i,j, 0, 0, lines,colummns,colour, 1, 1);
				dummyresult++;
			/*the last flag inibts comparision with (0,0) actively working as a dud, as the unused dummy result, the objective is to distinct different rooms only*/
				colour--; /*change colour*/
				vertex++; /*new room(aka Vertex) was mapped*/
				printf("%d\n", vertex);	
			}
		}
	}
	for (i=0; i< lines; i++){
                for(j=0; j< colummns; j++){
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");
	}
	 grapho->adjlist = (node**)calloc(1, (sizeof(node*) * (vertex))); /*alloc adjacency list array*/
	grapho->TotalVertex=vertex;
	for (i=0; i< lines; i++){
                for(j=0; j< colummns; j++){
                        if(check_breakability(matrix,i,j,lines,colummns)==1){
				if(j>0 && j < colummns){
					if((matrix[i][j-1]<-1 && matrix[i][j+1]<-1) && (matrix[i][j-1] != matrix[i][j+1])){
						grapho->adjlist[abs(matrix[i][j+1])-2] = CaIoUnode(abs(matrix[i][j-1])-2,matrix[i][j],i,j,grapho->adjlist[abs(matrix[i][j+1])-2]);
                				grapho->adjlist[abs(matrix[i][j-1])-2] = CaIoUnode(abs(matrix[i][j+1])-2,matrix[i][j],i,j,grapho->adjlist[abs(matrix[i][j-1])-2]);
					}
				}
				if(i>0 && i < lines){
					if((matrix[i-1][j]<-1 && matrix[i+1][j]<-1)&& (matrix[i][j-1] != matrix[i][j+1])){
                                        	grapho->adjlist[abs(matrix[i+1][j])-2] = CaIoUnode(abs(matrix[i-1][j])-2,matrix[i][j],i,j,grapho->adjlist[abs(matrix[i+1][j])-2]);
                                        	grapho->adjlist[abs(matrix[i-1][j])-2] = CaIoUnode(abs(matrix[i+1][j-1])-2,matrix[i][j],i,j,grapho->adjlist[abs(matrix[i-1][j])-2]);
                                	}
				}

			}
                }
        }

	return grapho;
}
void printgraph(graph* grapho){
	int i,r;
	node *aux=NULL;
   	for (i = 0; i < (grapho->TotalVertex); i++){
		r=(i*(-1))-2;
	    	printf("Connections to vertex [%d] corresponding to room [%d]", i, r);
        	for (aux = grapho->adjlist[i]; aux != NULL; aux = aux->next){
            		printf("Connected to node [%d],corresponding to room [%d], with cost [%d], through[%d][%d] ", aux->vertexID, (((aux->vertexID)*-1)-2), aux->edge_cost, aux->brokenLine, aux->brokenCol);
        	}
    	}
}

