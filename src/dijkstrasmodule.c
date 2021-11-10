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
static int hfree;     /* número de elementos existentes no acervo */
static int hsize;

void HPQinit(unsigned Size){
	Heap = (int *)calloc(Size,sizeof(int));
	hsize = Size;
	hfree = 0; 
}

void HPQinsert(int v){
/* All elements  */
	if ((hfree-1) < hsize) {
		Heap[hfree] = v;
		hfree++;
	}
}

int* dijsktras(graph *grapho, int s, int *st, double *wt){
	int v, w, i;
	bool InHeap=false, debug=false;
	node *aux;
	if(debug==true)
		printf("entered Dij");
	HPQinit(grapho->TotalVertex);
	for (v = 0; v < grapho->TotalVertex; v++){
		st[v] = -1;
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
						if(Heap[i]==w){
							InHeap=true;
							break;
						}
					}
					
					wt[w] = P;
					if(InHeap==false){
						HPQinsert(w);
						i=hfree-1;
					}
					FixUp(i, wt);
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

void FixDown(int Idx, int N, double *wt) {
	int Child; /* índice de um nó descendente */
	while(2*Idx < N-1) { /* enquanto não chegar às folhas */
		Child = 2*Idx+1;
		/* Selecciona o maior descendente.*/
		/* Nota: se índice Child é N-1, então só há um descendente */
		if (Child < (N-1)  &&  lessPri(Heap[Child], Heap[Child+1], wt)) Child++;
		if (!lessPri(Heap[Idx], Heap[Child],wt)) break; /* condição acervo */
		/* satisfeita*/
		exch(Heap[Idx], Heap[Child]);
		/* continua a descer a árvore */
		Idx = Child;
	}
}

void FixUp(int Idx, double* wt){
	while (Idx > 0  &&  lessPri(Heap[(Idx-1)/2], Heap[Idx], wt)) {
		exch(Heap[Idx], Heap[(Idx-1)/2]);
		Idx = (Idx-1)/2;
	}
}

int HPQdelmin(double *wt){
	/* troca maior elemento com último da tabela e reordena com FixDown */
	exch(Heap[0], Heap[hfree-1]);
	FixDown( 0, hfree-1 , wt); 
	/* ultimo elemento não considerado na reordenação */
	return Heap[--hfree]; 
}

bool HPQEmpty(){
return hfree == 0 ? true : false;
}
bool lessPri(int A, int B,  double* wt ){
	if(wt[A]>wt[B])
		return true;
	else
		return false;
}
