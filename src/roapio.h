/*-----------------------------------------------------------------------------------------------------+
| roapio.h               |Library for the Read/Write module (iomodule.c), containing dependencies,     |
|                        |read/write and auxiliary functions definitions and macros used.              |
|                        |                                                                             |
+------------------------------------------------------------------------------------------------------+
| Authors: Joao Barreiros C. Rodrigues nº99968, Henrique Ramos Delfino nº99957                         |
|          LEEC-IST                                                                                    |
| Date: 08 October 2021                                                                                |
+-----------------------------------------------------------------------------------------------------*/
#ifndef ROAPIO_H_INCLUDED
#define ROAPIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct graph graph;
void readwritefile(char*_filenamein, int sflag);
char* gen_outname(char* _filenamein, int sflag);
void check_inname(char* _filenamein,int sflag);
void recurprint_spath(int* st,double* wt, graph *grapho, FILE* fpout, int target, int* Wallnumber);
#endif

