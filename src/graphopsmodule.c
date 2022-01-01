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
#include "roapmatrix.h"

/*Function Name: CaIoUnode (Create and Insert or Update node)
  Input: 4 integers (data for node seeding- Vertex connected, edge_cost, broken wall coordinates)
  Output: 
  Date Created: 09 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: Seed nodes in a adjacency list for graph building
*/
node* CaIoUnode (int vertexID, int edge_cost, int brokenCol, int brokenLine,  node* target){
	node* new = target, *aux=NULL, *aux2=NULL;
	bool eflag= false;
        if(target!= NULL){
		if(target->next==NULL){ /*If there is only one node*/
			if((target->vertexID) == vertexID){ //find if adjacency is already in list
                                eflag=true;
                                aux=target;
                        }
		}
		else{
	                for(aux2=target;aux2!= NULL; aux2=aux2->next){
				if(aux2!=NULL)
					aux=aux2;
				if((aux->vertexID) == vertexID){
					eflag=true;
					break;
				}

			}
		}
		if(eflag==false){ /*ready new adjacency to be seeded*/
			new = (node*)malloc(sizeof(node));
			if(target->next==NULL)
				target->next=new;
			else
				aux->next=new;
		}
        }
        else{ /*initialize list*/
		if(eflag==false){
			new = (node*)malloc(sizeof(node));
                	new->vertexID = vertexID;
                	new->next=NULL;
                	new->edge_cost=edge_cost;
			new->brokenCol=brokenCol+1;
                	new->brokenLine=brokenLine+1;
               		return new;
		}
        }
	if(eflag==false){ /*Seed new adjacency*/
        	new->vertexID = vertexID;
        	new->next=NULL;
        	new->edge_cost=edge_cost;
		new->brokenCol=brokenCol+1;
                new->brokenLine=brokenLine+1;
	}
	else{ /*Update existing adjacency*/
		if((edge_cost < aux->edge_cost) || (edge_cost == aux->edge_cost)){ /*If new edge cost is cheaper or more recent (could have only been cheaper)*/
			aux->edge_cost= edge_cost;
			aux->brokenCol=brokenCol+1;
			aux->brokenLine=brokenLine+1;
		}
	}
        return target;
}
/*Function Name: CaBgraph (Create and Build Graph)
  Input: pointer to pointer to int (matrix), 4 integers (matrix lines and colummns and target coordinates), file pointer
  Output: pointer to graph struct.
  Date Created: 09 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: 
*/
graph* CaBgraph(int **matrix, int lines, int colummns, int targetcellline, int targetcellcol, FILE* fpout){  /*Create and Build Graph*/
	graph* grapho = NULL;
	int i=0, j=0, colour =-4, vertex=0;
	bool debug=false;
	targetcellline-=1;/*Update coordinates since the matrix starts at (0,0)*/
	targetcellcol-=1;
	if(debug==true)
		printf("target: %d %d", targetcellline, targetcellcol);
	 if(targetcellline<0 || targetcellline+1> lines || targetcellcol<0 || targetcellcol+1>colummns || matrix[targetcellline][targetcellcol] !=0){ /*check if treasure is out of bound or is non-white*/
                fprintf(fpout,"-1\n\n"); /*pass to file*/
                return grapho;
        }
	 /*Start with flooding both start and end room, as they need to be fixed colours*/
	Queuedflood_room(matrix, 0, 0,lines, colummns, start);
	if(matrix[targetcellline][targetcellcol]==start){ /*check if they are in the same room*/
		fprintf(fpout,"0\n\n"); /*pass to file*/
		return grapho;
	}
	Queuedflood_room(matrix, targetcellline, targetcellcol,lines, colummns, end);
	vertex=2; /*every room is a vertex in the graph, 1(start)+1(end)=2*/
	for (i=0; i< lines; i++){
		for(j=0; j< colummns; j++){
			if(matrix[i][j]==0){
				Queuedflood_room(matrix, i, j,lines, colummns, colour);
				colour--; /*change colour*/
				vertex++; /*new room(aka Vertex) was mapped*/
				if(debug==true)
					printf("%d\n", vertex);	
			}
		}
	}
	if(debug==true){ /*debug section for matrix printing*/
		for (i=0; i< lines; i++){
                	for(j=0; j< colummns; j++){
				if(matrix[i][j]>=0)
					printf(" %d ", matrix[i][j]);
				else
					printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
	}/*end of debug section*/
	grapho = (graph*)malloc(sizeof(graph));
	grapho->adjlist = (node**)calloc(1, (sizeof(node*) * (vertex))); /*alloc adjacency list array*/
	grapho->TotalVertex=vertex;
	for (i=0; i< lines; i++){
                for(j=0; j< colummns; j++){
                        if(check_breakability(matrix,i,j,lines,colummns)==1){
				if(j>0 && j < colummns-1){ /*check if the cell breakability is compromised by a horizontal bound [inhibts horizontal travel]*/
					if((matrix[i][j-1]<-1 && matrix[i][j+1]<-1) && (matrix[i][j-1] != matrix[i][j+1])){
						grapho->adjlist[-(matrix[i][j+1])-2] = CaIoUnode(-(matrix[i][j-1])-2,matrix[i][j],j,i,grapho->adjlist[-(matrix[i][j+1])-2]); /*The adjacency is made both-ways in */
																					     /*in the adjacency lists [A-B and B-A]*/
                				grapho->adjlist[-(matrix[i][j-1])-2] = CaIoUnode(-(matrix[i][j+1])-2,matrix[i][j],j,i,grapho->adjlist[-(matrix[i][j-1])-2]);
					}
				}
				if(i>0 && i < lines-1){  /*check if the cell breakability is compromised by a vertical bound [inhibts vertical travel]*/
					if((matrix[i-1][j]<-1 && matrix[i+1][j]<-1)&& (matrix[i-1][j] != matrix[i+1][j])){
                                        	grapho->adjlist[-(matrix[i+1][j])-2] = CaIoUnode(-(matrix[i-1][j])-2,matrix[i][j],j,i,grapho->adjlist[-(matrix[i+1][j])-2]);
                                        	grapho->adjlist[-(matrix[i-1][j])-2] = CaIoUnode(-(matrix[i+1][j])-2,matrix[i][j],j,i,grapho->adjlist[-(matrix[i-1][j])-2]);
                                	}
				}

			}
                }
		if(i>0)
			free(matrix[i-1]); /*Free previous line, a buffer is needed in order to be able to check vertical travel*/
        }
	free(matrix[lines-1]); /*free the remainder of matrix associated blocks, the last line and the matrix itself*/
	free(matrix);
	return grapho;
}
/*Function Name: printgraph
  Input: pointer to graph struct, 
  Output: None. Graph printed in stdout
  Date Created: 08 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: Print a given graph
*/
void printgraph(graph* grapho){
	int i,r;
	node *aux=NULL;
   	for (i = 0; i < (grapho->TotalVertex); i++){
		r=(i*(-1))-2;
	    	printf("vertex [%d] corresponding to room [%d]\n", i, r);
        	for (aux = grapho->adjlist[i]; aux != NULL; aux = aux->next){
            		printf("Connected to node [%d],corresponding to room [%d], with cost [%d], through[%d][%d] \n", aux->vertexID, (((aux->vertexID)*-1)-2), aux->edge_cost, aux->brokenLine, aux->brokenCol);
        	}
    	}
}

