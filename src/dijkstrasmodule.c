/*-----------------------------------------------------------------------------------------------------+
| dikjstrasmodule.c      |Final phase Dijkstras MST algorithm and queue based functions                |
|                        |module for roapmain.c                                                        |
|                        |Mostly reskinned and edited code from AED-Powerpoints 10 and 13              |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 08 November 2021                                                                               |
+-----------------------------------------------------------------------------------------------------*/
#include "roapdijkstras.h"
static int *Heap;
static int hfree;     /* número de elementos existentes no acervo */
static int hsize;

void HPQinit(unsigned Size){
	Heap = (int *)malloc(Size*sizeof(int));
	hsize = Size;
	free = 0; 
}

void HPQinsert(int v){
/* All elements  */
	if ((free+1) < hsize) {
		Heap[free] = v;
		free++;
	}
}

int* djisktras(Graph *grapho, int s, int *st, double *wt){
	int v, w, i;
	bool InHeap=false;
	node *aux;
	HPQinit(grapho->TotalVertex);
	for (v = 0; v < grapho->TotalVertex; v++){
		st[v] = -1;
		wt[v] = INT_MAX;
		HPQinsert(v);
	}
	wt[s] = 0.0;
	while (!HPQempty()){
		if(Heap[0]==1) /*Verifies if top node is 1 aka Treasure Room*/
		if (wt[v = PQdelmin()] != INT_MAX)
			for (aux = grapho->adjlist[v]; aux != NULL; aux = aux->next){
				if (wt[w = aux->vertexID] > P){
					for(i=0; i<=free; i++){
						if(Heap[i]==w){
							InHeap=true;
							break;
						}
					}
					
					wt[w] = P;
					if(InHeap==false){
						HPQinsert(w);
						i=free-1;
					}
					FixUp(i);
					st[w] = v;
				}
				InHeap=false;
			}
	}
	return st;
}

void FixDown(int Heap[], int Idx, int N) {
	int Child; /* índice de um nó descendente */
	while(2*Idx < N-1) { /* enquanto não chegar às folhas */
		Child = 2*Idx+1;
		/* Selecciona o maior descendente.*/
		/* Nota: se índice Child é N-1, então só há um descendente */
		if (Child < (N-1)  &&  lessPri(Heap[Child], Heap[Child+1])) Child++;
		if (!lessPri(Heap[Idx], Heap[Child])) break; /* condição acervo */
		/* satisfeita*/
		exch(Heap[Idx], Heap[Child]);
		/* continua a descer a árvore */
		Idx = Child;
	}
}

void FixUp(int Idx){
	while (Idx > 0  &&  lessPri(Heap[(Idx-1)/2], Heap[Idx])) {
		exch(Heap[Idx], Heap[(Idx-1)/2]);
		Idx = (Idx-1)/2;
	}
}

int PQdelmin(){
	/* troca maior elemento com último da tabela e reordena com FixDown */
	exch(Heap[0], Heap[hfree-1]);
	FixDown(Heap, 0, hfree-1); 
	/* ultimo elemento não considerado na reordenação */
	return Heap[--hfree]; 
}

bool PQEmpty() {
return hfree == 0 ? true : false;
}
