/*-----------------------------------------------------------------------------------------------------+
| alphaopsmodule.c       |1st phase operative functions module for RoaPmain.c                          |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 05 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#include <roap.h>

// START 05 Out Im going to sleep
// 
int variant_test(int** matrix, int targetcellline, int targetcellcol, int targetcellline2, int targetcellcol2, char varID[2], int lines, int colummns){
	targetcellline -=1; //update to target to be on pair with a matrix starting in (0,0)
	targetcellcol -=1;
	targetcellline2 -=1;
	targetcellcol2 -=1;
	int result = -3;
	int extractedID=0;
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
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, white)
		break;
		case '3':
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, grey)
		break;
		case '4':
			result=check_neighbours(matrix, targetcellline, targetcellcol, lines, colummns, black)
		break;
		case '5':
			result=check_breakability
		break;
		case '6':
	}
	return result;
}

int check_neighbours (int** matrix, int targetcelllline, int targetcellcol, int lines, int columns, int colour){
	int bounds[4]={0,0,0,0};
	if(targetcellline > (lines-1) || targetcellline < 0 || targetcellcol > (colummns-1) || targetcellcol < 0){
                result=-2;
		return result;
	}
	bounds=check_bounds(targetcellline, targetcellcol,lines, colummns);
	if(colour==white||colour==black){
		if(bound[left]==0){
			if(matrix[targetcellline][targetcellcol-1]==colour)
				result=1;
		}
		if(bound[up]==0){
			if(matrix[targetcellline+1][targetcellcol]==colour)
                                result=1;
		}
		if(bound[down]==0){
			if(matrix[targetcellline-1][targetcellcol]==colour)
                                result=1;
		}
		if(bound[right]==0){
			if(matrix[targetcellline][targetcellcol+1]==colour)
                                result=1;
		}
                        
       	}
       	else{ //grey cell search
		if(bound[left]==0){
                        if(matrix[targetcellline][targetcellcol-1]>0)
                                result=1;
                }
                if(bound[up]==0){
                        if(matrix[targetcellline+1][targetcellcol]>0)
                                result=1;
                }
                if(bound[down]==0){
                        if(matrix[targetcellline-1][targetcellcol]>0)
                                result=1;
                }
                if(bound[right]==0){
                        if(matrix[targetcellline][targetcellcol+1]>0)
                                result=1;
                }
        
	}

}

int check_breakability(int** matrix, int targetcelllline, int targetcellcol, int lines, int columns){
	int bounds[4]={0,0,0,0};
        if(targetcellline > (lines-1) || targetcellline < 0 || targetcellcol > (colummns-1) || targetcellcol < 0){
                result=-2;
                return result;
        }

        bounds=check_bounds(targetcellline, targetcellcol,lines, colummns);
}

int* check_bounds(int targetcellline, int targetcellcol, int lines, int colummns){
	int bounds[4]={0,0,0,0};//left,up,down,right
	if(targetcellcol==0)
		bounds[left]=1; //implement macro!
	if (targetcellline==0)
		bounds[up]=1;
	if (targetcellline==(lines-1))
		bounds[down]=1;
	if (targetcellcol==(colummns-1))
		bounds[right]=1;
	return bounds;
}
