/*-----------------------------------------------------------------------------------------------------+
| roapmain.c             |Main module for the Algoritmos e Estruturas de Dados course project - Raiders|
|                        |of all Pyramids (RoaP), a pathfinding-based project.                         |
|                        |Version f1.2                                                                 |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 09 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#include "roapmain.h"
#include "roapio.h"
#include "roaphelp.h"

int main(int argc, char *argv[]){
    
    char  *_filenamein = NULL;
    int opt=0, sflag=0, fflag=0;

    	if (argc == 2 && argv[1][0]!='-' && argv[1][1]!='s'&& argv[1][2]!=' '){ /*If there is only two arguments and the second does not coincide with "-s" argument*/
                        _filenamein =argv[1]; 
                        fflag=1; /*Final Phase is engaged*/
                }

	while((opt = getopt(argc, argv, OPTION_LIST)) != -1){ /*Pass to getop*/
	 	if (argc < 2) {
      			help(Argument_Error, Missing_Argument);
   		}
	 	if(argc > 3){
			help(Argument_Error, Argument_Overflow);
	 	}
		if (argc == 2 && argv[1][0]!='-' && argv[1][1]!='s'&& argv[1][2]!=' '){ /*fail safe*/
			_filenamein =argv[1];
			fflag=1;
		}
		if(fflag !=1){
        		switch (opt){
        			case 'h':
          				help(User_Called_Help, '0');
        	
				break;
				case 's': /*Obligatory argument option*/
            				if (optarg == NULL)
                				help(Argument_Error, Missing_Argument);
            				sflag = 1;
	    			_filenamein = optarg;
        			break;
        			case ':':
        	    			help(Argument_Error, Missing_Argument);
				break;
        			case '?':
            				if (isprint (optopt))
                				help(Argument_Error, Unknown_Argument);
				break;
	       		}
		}
      }
	if(sflag==1 || fflag==1)
		readwritefile(_filenamein, sflag); /*Pass control do readwrite function*/
	return(0);
}

