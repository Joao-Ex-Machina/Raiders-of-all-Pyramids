/*-----------------------------------------------------------------------------------------------------+
| basicopsmodule.c       |1st phase operative operations modules for roapmain.c                        |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#include "roapbops.h"
#include "roaphelp.h"
/*Function Name: variant_test
  Input: Indicated downward (TMTA)
  Output: Integer (result)
  Date Created: 05 Out 2021
  Last Revised: 12 Out 2021
  Definition: Main result management function
*/
int variant_test(int** matrix, int targetcellline, int targetcellcol, int targetcellline2, int targetcellcol2, char varID[2], int lines, int colummns){
	targetcellline -=1; //update to target to be on pair with a matrix starting in (0,0)
	targetcellcol -=1;
	targetcellline2 -=1;
	targetcellcol2 -=1;
	int result = -3;
	if(varID[0]!='A')
		help(Read_Error, Unknown_Operation);
	switch(varID[1]){
		case '1':
			if(targetcellline > (lines-1) || targetcellline < 0 || targetcellcol > (colummns-1) || targetcellcol < 0 )
				result=-2;
			else{
				result=matrix[targetcellline][targetcellcol];
			}
		break;
		case '2':
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, white);
		break;
		case '3':
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, grey);
		break;
		case '4':
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, black);
		break;
		case '5':
			result=check_breakability(matrix, targetcellline, targetcellcol, lines, colummns);
		break;
		case '6':
			if(targetcellline < 0 ||targetcellline2 < 0 || targetcellline >(lines-1) || targetcellline2 > (lines-1) || targetcellcol < 0 ||targetcellcol2 < 0 || targetcellcol >(colummns-1) || targetcellcol2 > (colummns-1))
                        result =-2;
			else{
				Queuedflood_room(matrix, targetcellline, targetcellcol,lines, colummns, path);
					if(matrix[targetcellline2][targetcellcol2]==path)
						result=1;
					else
						result=0;
				}
		break;
	}
	return result;
}

/*Function Name: check_neighbours
  Input: 5 integers, pointer to pointer to int (matrix)
  Output: Integer
  Date Created: 06 Out 2021
  Last Revised: 07 Out 2021
  Definition: Check crossed neighbours of a cell
*/
int check_neighbours (int** matrix, int targetcellline, int targetcellcol, int lines, int colummns, int colour){
	int result=0;
	int* bounds=0;
	if(targetcellline > (lines-1) || targetcellline < 0 || targetcellcol > (colummns-1) || targetcellcol < 0){
                result=-2;
		return result;
	}
	bounds=check_bounds(targetcellline, targetcellcol,lines, colummns);
	if(colour==white||colour==black){
		if(bounds[left]==0){
			if(matrix[targetcellline][targetcellcol-1]==colour)
				result=1;
		}
		if(bounds[up]==0){
			if(matrix[targetcellline-1][targetcellcol]==colour)
                                result=1;
		}
		if(bounds[down]==0){
			if(matrix[targetcellline+1][targetcellcol]==colour)
                                result=1;
		}
		if(bounds[right]==0){
			if(matrix[targetcellline][targetcellcol+1]==colour)
                                result=1;
		}
                        
       	}
       	else{ //grey cell search
		if(bounds[left]==0){
                        if(matrix[targetcellline][targetcellcol-1]>0)
                                result=1;
                }
                if(bounds[up]==0){
                        if(matrix[targetcellline-1][targetcellcol]>0)
                                result=1;
                }
                if(bounds[down]==0){
                        if(matrix[targetcellline+1][targetcellcol]>0)
                                result=1;
                }
                if(bounds[right]==0){
                        if(matrix[targetcellline][targetcellcol+1]>0)
                                result=1;
                }
        
	}
	free(bounds);
	return result;
}
 /*Function Name: check_breakability
  Input: four integers, pointer to pointer to integers
  Output: integer (result)
  Date Created: 07 Out 2021
  Last Revised: 07 Out 2021
  Definition: Check is a grey cell is breakble (one straight path is makeable )
*/
int check_breakability(int** matrix, int targetcellline, int targetcellcol, int lines, int colummns){
	int* bounds=0;
	int result=0;
        if(targetcellline > (lines-1) || targetcellline < 0 || targetcellcol > (colummns-1) || targetcellcol < 0){
                result=-2;
        	return result;
        }

        bounds=check_bounds(targetcellline, targetcellcol,lines, colummns);
	if(matrix[targetcellline][targetcellcol]<=white){ //check if cell is grey
		result=-1;
		free(bounds);
		return result;
	}

	if(bounds[left]==0 && bounds[right]==0){ //Verify if there's any bound. In positive case discard that path
		if((matrix[targetcellline][targetcellcol-1]==0 && matrix[targetcellline][targetcellcol+1]==0) || (matrix[targetcellline][targetcellcol-1]<-1 && matrix[targetcellline][targetcellcol+1]<-1)){
			result=1;
			free(bounds);
			return result;
		}

	}
	if(bounds[up]==0 && bounds[down]==0){
                if((matrix[targetcellline-1][targetcellcol]==0 && matrix[targetcellline+1][targetcellcol]==0) || (matrix[targetcellline-1][targetcellcol]<-1 && matrix[targetcellline+1][targetcellcol]<-1)){
                        result=1;
			free(bounds);
			return result;
                }

        }
	free(bounds);
	return result;
}
/*Function Name: check_bounds
  Input: 4 integers 
  Output: array of integers
  Date Created: 07 Out 2021
  Last Revised: 07 Out 2021
  Definition: Main check bounds function
*/
int* check_bounds(int targetcellline, int targetcellcol, int lines, int colummns){
	int* bounds=(int*)calloc(4, sizeof(int));
	if(targetcellcol==0)
		bounds[left]=1; //macro implemented
	if (targetcellline==0)
		bounds[up]=1;
	if (targetcellline==(lines-1))
		bounds[down]=1;
	if (targetcellcol==(colummns-1))
		bounds[right]=1;
	return bounds;
}
/*Function Name: flood_room
  Input: As indicated below (TMTA)
  Output: Integer
  Date Created: 12 Out 2021
  Last Revised: 16 Out 2021 (added flood prediction)
  Definition: Flood-based algorithm to discover if two cells are in the same room. Unused in final phase for stack overflow from recursion
*/
int flood_room(int** matrix, int targetcellline, int targetcellcol,int targetcellline2, int targetcellcol2, int lines, int colummns,int colour, bool firstflag, bool justfloodflag){
	bool debug = false;
	int result=0;
	if(firstflag==1){
		if(targetcellline < 0 ||targetcellline2 < 0 || targetcellline >(lines-1) || targetcellline2 > (lines-1) || targetcellcol < 0 ||targetcellcol2 < 0 || targetcellcol >(colummns-1) || targetcellcol2 > (colummns-1)){
			result =-2;
			return result;
		}
	}
	if(firstflag==0){
                if(targetcellline < 0 ||targetcellline2 < 0 || targetcellline > (lines-1) || targetcellline2 > (lines-1) || targetcellcol < 0 ||targetcellcol2 < 0 || targetcellcol > (colummns-1) || targetcellcol2 > (colummns-1))
                return 0;
        }
	if(justfloodflag==false){
		if(matrix[targetcellline2][targetcellcol2]==path){ //no need to continue path-finding
        		result =1;
			return result;
		}
	}

	if(matrix[targetcellline][targetcellcol]==white){
		matrix[targetcellline][targetcellcol]=colour;
		if(debug==true)
			printf("%d %d \n", targetcellline, targetcellcol);
		if(targetcellline < (lines-1) && (matrix[targetcellline+1][targetcellcol] == white)) //used in order to reduced memory allocated by check_bounds() and predict flood
			flood_room(matrix,targetcellline+1,targetcellcol, targetcellline2, targetcellcol2, lines,colummns,colour, 0, justfloodflag);
		if(targetcellcol < (colummns-1)  && (matrix[targetcellline][targetcellcol+1] == white))
                        flood_room(matrix,targetcellline,targetcellcol+1, targetcellline2, targetcellcol2, lines,colummns, colour,0, justfloodflag);
		if(targetcellline > 0 && (matrix[targetcellline-1][targetcellcol] == white))
			flood_room(matrix,targetcellline-1,targetcellcol, targetcellline2, targetcellcol2, lines,colummns, colour,0, justfloodflag);
		if(targetcellcol > 0 && (matrix[targetcellline][targetcellcol-1] == white))
			flood_room(matrix,targetcellline,targetcellcol-1, targetcellline2, targetcellcol2, lines,colummns, colour, 0, justfloodflag);
	}
	else
		return 0;
	if(firstflag==1) {		//confirm we are back to the first instance of the function
		if(matrix[targetcellline2][targetcellcol2]==colour)
			result =1;	
	}
	return result;
}

/*Function Name: Queuedflood_room
  Input: Pointer to pointer to integer (matrix), 2 ints (target coordinates), 2 ints (Total lines and colummns of matrix), 1 int (new colour of room)
  Output: pointer to integer st, Althought it could also be a void function with no return.
  Date Created: 11 Nov 2021
  Last Revised: 11 Nov 2021
  Definition: Flood room algorithm based on the above but iteration-driven with assistance from a queue
*/
void Queuedflood_room(int** matrix, int targetcellline, int targetcellcol,int lines, int colummns, int colour){
	floodnode* last=NULL, *popped=NULL, *pushed=NULL, *nextpop=NULL;
	last=(floodnode*)malloc(sizeof(floodnode));
	matrix[targetcellline][targetcellcol]=colour;
	last->line=targetcellline;
	last->col=targetcellcol;
	last->next=NULL;
	popped=last;
	nextpop=last;
	while(nextpop!=NULL){ /*effectively while the queue is not empty*/
			popped=nextpop;
			if(popped==NULL)/*effectively if the queue empty*/
				break;
			matrix[(popped->line)][(popped->col)]=colour; /*dyes cell*/
			if((popped->line)< (lines-1) && (matrix[(popped->line)+1][popped->col] == white)){ 	/*checks if adjacent is in the matrix */
														/*and if it is white (which also checks if it has been visited)*/
				matrix[(popped->line)+1][(popped->col)]=colour; 
				pushed=(floodnode*)malloc(sizeof(floodnode));
				pushed->line=(popped->line)+1; /*add target coordinates to node*/
				pushed->col=(popped->col);
				pushed->next=NULL;
				last->next=pushed; /*pushed node is linked to the last node in queue*/
				last=pushed; /*Pushed node is now the last node on queue*/
			} 
                	/*Repeat for remaining cross adjacencies*/

                	if((popped->col) < (colummns-1)  && (matrix[(popped->line)][(popped->col)+1] == white)){
				matrix[(popped->line)][(popped->col)+1]=colour;
				pushed=(floodnode*)malloc(sizeof(floodnode));
                        	pushed->line=(popped->line);
                        	pushed->col=(popped->col)+1;
				pushed->next=NULL;
                       		last->next=pushed;
                        	last=pushed;
			}
                        
                	if((popped->line) > 0 && (matrix[(popped->line)-1][(popped->col)] == white)){
				matrix[(popped->line)-1][(popped->col)]=colour;
				pushed=(floodnode*)malloc(sizeof(floodnode));
                        	pushed->line=(popped->line)-1;
                        	pushed->col=(popped->col);
				pushed->next=NULL;
                        	last->next=pushed;
                        	last=pushed;
			}
                        
                	if((popped->col) > 0 && (matrix[(popped->line)][(popped->col)-1] == white)){
				matrix[(popped->line)][(popped->col)-1]=colour;
				pushed=(floodnode*)malloc(sizeof(floodnode));
                        	pushed->line=(popped->line);
                        	pushed->col=(popped->col)-1;
				pushed->next=NULL;
                        	last->next=pushed;
                        	last=pushed;
			}
		if(popped->next==NULL){ /*check if it is the last element to be popped effectively if queue is empty*/
			free(popped); /*pop node*/
			break; /*return*/
		}
			
		else
			nextpop=popped->next; /*the above element to the popped node is the next to be popped*/

		free(popped); /*pop node*/
	}

}
