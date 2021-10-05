#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
int working = 0, opt;
int controlfile = 1; /*variable to control the read file */
FILE *fp;

    /* must have at least one argument besides the exec name */
   if (argc < 2) {
      usage(argv[0]);
      exit(0);
   }

 while ((opt = getopt(argc, argv, "s")) != -1) {
      
      controlfile++;
      switch (opt) {
          case 's':/*case the first argument is s*/
            working = 1;
            break;
      default: /* '?' */
         usage(argv[0]);
         exit(0);
      }
   }
    /* read the file */
   fp = (FILE *) fopen(argv[controlfile], "r");
   if (fp == (FILE *) NULL) {
      fprintf(stderr, "File %s cannot be read.  Please correct.\n", argv[1]);
      exit(0);
   }

}

