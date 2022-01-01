/*-----------------------------------------------------------------------------------------------------+
| dijkstrasmodule.c      |Final phase Dijkstras MST algorithm and queue based functions                |
|                        |module for roapmain.c                                                        |
|                        |Mostly reskinned and edited code from AED-Powerpoints 10 and 13              |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 08 November 2021                                                                               |
+-----------------------------------------------------------------------------------------------------*/
#include "roapdijkstras.h"
#include "roapgrops.h"
static int *Heap;
static int hfree;     /*Heap ocupancy*/
static int hsize;     /*Max Heap Size*/
/*
Although not recommended we have proceded with R. Sedgewick implementation that was shown in class
The implemented static variables were kept to reduced the number of alterations to fuctions (adding 
new inputs such as a pointer to hfree and the Heap which we would be operating over) and variables 
(hfree would have to be passed through a pointer) to a otherwise functional and efficient code
The group considered that although not ideal the static variables could be kept since
they are inacessible through other files (which was the intended) having more control over them 
than say a global declared variable
*/

/*Function Name: HPQinit
  Input: unsigned integer (Desired size of Heap, which will be the total number of vertex in the graph)
  Output: None. Heap is alloc'ed
  Date Created: 08 Nov 2021
  Last Revised: 08 Nov 2021
  Definition: Initializes Heap array with the number of vertex to be used
*/
void HPQinit(unsigned Size){
	Heap = (int *)calloc(Size,sizeof(int));
	if(Heap==NULL)
		exit(1);
	hsize = Size;
	hfree = 0; 
}
/*Function Name: HPQinsert
  Input: signed integer (a vertex)
  Output: None. Value is stored in Heap
  Date Created: 08 Nov 2021
  Last Revised: 08 Nov 2021
  Definition: Inserts a vertex in the heap. Increases hfree (heap ocupancy)
*/
void HPQinsert(int v){
	if ((hfree-1) < hsize) { //Heap starts at [0]
		Heap[hfree] = v;
		hfree++;
	}
}

/*Function Name: dijkstras 
  Input: pointer to graph struct, 1 integer (starting vertex), 1 pointer to integer (spanning tree), 1 pointer to double precision float (weighted tree), which could have been also a pointer to integer,
  since all edge costs are integers.
  Output: pointer to integer st, Althought it could also be a void function with no return.
  Date Created: 08 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: Run Dijkstras greedy algorithm on the given graph in order to find the shortest path between node s (which is always node 0 aka starting room) and node 1 (which is the treasure room)
*/
int* dijsktras(graph *grapho, int s, int *st, double *wt){
	int v, w, i;
	bool InHeap=false, debug=false;
	node *aux;
	if(debug==true)
		printf("entered Dij");
	HPQinit(grapho->TotalVertex);
	for (v = 0; v < grapho->TotalVertex; v++){
		st[v] = -1;     /*Set as if all vertex would be disconnected*/
		wt[v] = INT_MAX;
	}
	HPQinsert(0);
	wt[s] = 0.0;
	while (!HPQEmpty()){
		if(Heap[0]==1) /*Verifies if top node is 1 aka Treasure Room*/
			break;
		if (wt[v =HPQdelmin(wt)] != INT_MAX){
			for (aux = grapho->adjlist[v]; aux != NULL; aux = aux->next){
				if (wt[w = aux->vertexID] > P){
					for(i=0; i<=hfree; i++){
						if(Heap[i]==w){ /*Searches if adjacent needed node is in heap*/
							InHeap=true; 
							break;
						}
					}
					
					wt[w] = P; /*Updates path through weight update*/
					if(InHeap==false){
						HPQinsert(w); /*Insert needed adjacent node*/
						i=hfree-1; /*Updates i to the now inserted node*/
					}
					FixUp(i, wt); /*Updates priority*/
					st[w] = v;
				}
				InHeap=false;
			}
		}
	}
	if(debug==true)
		printf("ready to return from Dij");
	free(Heap);
	return st;
}
/*Function Name: FixDown
  Input: 2 Integers (Index and vertex cap), pointer to double (weight tree)
  Output: 
  Date Created: 08 Nov 2021
  Last Revised: 09 Nov 2021
  Definition: Updates priority of Idx in case its has lowered
*/
void FixDown(int Idx, int N, double *wt) {
	int Child; /*Index of child vertex*/
	while(2*Idx < N-1) { /* until it hasnt reached the lowest node*/
		Child = 2*Idx+1;
		/* Selects the heavyest child node*/
		if (Child < (N-1)  &&  lessPri(Heap[Child], Heap[Child+1], wt)) Child++;
		if (!lessPri(Heap[Idx], Heap[Child],wt)) break; /* condição acervo */
		exch(Heap[Idx], Heap[Child]);
		/* Continues going down the tree*/
		Idx = Child;
	}
}
/*Function Name: FixUp
  Input: Integer (Index), pointer to double (weight tree)
  Output: None directly. Heap order is changed
  Date Created: 08 Nov 2021
  Last Revised: 09 Nov 2021
  Definition: Updates priority of Idx in case its has increased
*/
void FixUp(int Idx, double* wt){
	while (Idx > 0  &&  lessPri(Heap[(Idx-1)/2], Heap[Idx], wt)) {
		exch(Heap[Idx], Heap[(Idx-1)/2]);
		Idx = (Idx-1)/2;
	}
}
/*Function Name: HPQdelmin
  Input:pointer to double (weight tree)
  Output: return Second to last element (last element to be reordered)
  Date Created: 08 Nov 2021
  Last Revised: 09 Nov 2021
  Definition: 
*/
int HPQdelmin(double *wt){
	/*Exchange first and last Heap elements */
	exch(Heap[0], Heap[hfree-1]);
	FixDown( 0, hfree-1 , wt); 
	/* last element is not considered in reordering*/
	return Heap[--hfree]; 
}
/*Function Name: HPQEmpty
  Input: No direct input, hfree is a static variable
  Output: boolean
  Date Created: 08 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: Check if Heap is empty
*/
bool HPQEmpty(){
return hfree == 0 ? true : false;
}
/*Function Name: LessPri
  Input: 2 Integers, one pointer to integer
  Output: boolean
  Date Created: 08 Nov 2021
  Last Revised: 10 Nov 2021
  Definition: verifies priority based on weight
*/
bool lessPri(int A, int B,  double* wt ){
	if(wt[A]>wt[B])
		return true;
	else
		return false;
}
