/*-----------------------------------------------------------------------------------------------------+
| basicopsmodule.c       |1st phase operative non-pathfinding operations for roapmain.c                |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#include "roapbops.h"
#include "roaphelp.h"
// START 05 Out Im going to sleep
// revised on 07 oct
//
int variant_test(int** matrix, int targetcellline, int targetcellcol, int targetcellline2, int targetcellcol2, char varID[2], int lines, int colummns){
	targetcellline -=1; //update to target to be on pair with a matrix starting in (0,0)
	targetcellcol -=1;
	targetcellline2 -=1;
	targetcellcol2 -=1;
	int result = -3;
	if(varID[0]!='A')
		help(Read_Error, Unknown_Operation); //TBI
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
			//TBI
		break;
	}
	return result;
}

//started on 06 oct
//revised 07 oct
int check_neighbours (int** matrix, int targetcellline, int targetcellcol, int lines, int colummns, int colour){
	int result=0;
	int* bounds;
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
	return result;
}
 //07 oct
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
		return result;
	}

	if(bounds[left]==0 && bounds[right]==0){ //Verify if there's any bound. In positive case discard that path
		if(matrix[targetcellline][targetcellcol-1]==0 && matrix[targetcellline][targetcellcol+1]==0){
			result=1;
			return result;
		}

	}
	if(bounds[up]==0 && bounds[down]==0){
                if(matrix[targetcellline-1][targetcellcol]==0 && matrix[targetcellline+1][targetcellcol]==0){
                        result=1;
			return result;
                }

        }

	return result;
}
//07 oct
int* check_bounds(int targetcellline, int targetcellcol, int lines, int colummns){
	static int bounds [4]={0,0,0,0};//left,up,down,right
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
