/*-----------------------------------------------------------------------------------------------------+
| roapgrops.h            |Final phase data structures and fuction definitions for graphsopsmodule.c    |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 November 2021                                                                               |
+-----------------------------------------------------------------------------------------------------*/
typedef struct node{
	struct node *next;
    	int vertexID; /*Room Identifier*/
    	int edge_cost; /*Broken cell cost*/
    	int brokenCol; /*Broken cell coordinates*/
    	int brokenLine;
}node;

typedef struct graph{
    	node **adjlist;
    	int TotalVertex; /*Total Rooms*/
}graph;
node* CaIoUnode (int nodeID, int branch_cost, int brokenCol, int brokenLine,  node* target);
graph* CaBgraph(int **matrix, int lines, int colummns, int targetcellline, int targetcellcolummn, FILE* fpout);
void printgraph(graph* grapho);
#define start -2
#define end -3
