/*-----------------------------------------------------------------------------------------------------+
| helpmodule.c           |Help manager module for roapmain.c                                           |
|                        |                                                                             |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 09 Oct 2021                                                                                    |
+-----------------------------------------------------------------------------------------------------*/
#include "roaphelp.h"

/*Function Name: help
  Input: An integer and a char corresponding to the error code
  Output: No return.
  Date Created: 09 Oct 2021
  Last Revised: 09 Oct 2021
  Definition: Help manager function. Note that programs are aborted with diferent exit codes for easier compreension
*/
void help(int Primary_ErrorCode,char Secondary_ErrorCode){
    if (Primary_ErrorCode !=0)
        printf("Error type %d%c \n", Primary_ErrorCode, Secondary_ErrorCode);
    switch (Primary_ErrorCode){
        case 0:
            printf(HELP_MESSAGE); //user called help
            exit(0);
        break;
        case 1:
            perror(" Command Prompt Argument Error:");
            switch (Secondary_ErrorCode){
                case 'A':
                    perror("Unknown Argument");
                    exit(101);
                    break;
                case 'B':
                    perror(" Missing Argument");
                    exit(102);
                    break;
                case 'C':
                    perror(" Argument Overflow");
                    exit(103);
                    break;
            }
        break;
        case 2:
            perror(" Read File Error:");
            switch (Secondary_ErrorCode){
                case '0':
                    	perror(" Unable to open file to read.\n Check if the desired file is in the same directory as the .out, remember that the program is case and extension sensitive ");
                    	exit(200);
                    	break;
                case 'A':
                    	perror(" Unsupported Extension on File");
                    	exit(201);
                    	break;
		case 'B':
		     	perror("Unknown operation on File");
			exit(202);
			break;
            }
        break;
    }
}
