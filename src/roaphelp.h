/*-----------------------------------------------------------------------------------------------------+
| roaphelp.h             |Main library for helpmodule.c and secondary library for other modules        |
|                        |Contains help functions and help codes definitions                           |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 08 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#ifndef ROAPHELP_H_INCLUDED
//dependencies
#include <stdio.h>
#include <stdlib.h>
//Macro definitions
#define User_Called_Help 0
#define Argument_Error 1
#define Unknown_Argument 'A'
#define Missing_Argument 'B'
#define Argument_Overflow 'C'
#define Read_Error 2
#define File_Not_Found '0'
#define Unsupported_Extension 'A'
#define Unknown_Operation 'B'
#define Bad_Info 'C'
#define HELP_MESSAGE "USER CALLED HELP\n VALID INPUTS:\n -h Displays this message \n -s [filename.in1]: Runs alpha version tests based on inserted file"
//Function definition
void help(int Primary_ErrorCode,char Secondary_ErrorCode);
#define ROAPHELP_H_INCLUDED
#endif
