#compiler
CC = gcc
#compile flags (in the valgrind debugging stage the flag -ggdb3 was also being used
CFLAGS  = -Wall -std=c99 -O3
#executable
default: roap
#Linking
roap:  roapmain.o iomodule.o matrixmodule.o basicopsmodule.o helpmodule.o
	$(CC) $(CFLAGS) -o roap roapmain.o iomodule.o matrixmodule.o basicopsmodule.o helpmodule.o
#Compilation of the object files
roapmain.o:  roapmain.c roapmain.h roaphelp.h roapio.h
	$(CC) $(CFLAGS) -c roapmain.c

iomodule.o: iomodule.c roapio.h roaphelp.h roapbops.h roapmatrix.h
	$(CC) $(CFLAGS) -c iomodule.c

matrixmodule.o: matrixmodule.c roapmatrix.h
	$(CC) $(CFLAGS) -c matrixmodule.c

basicopsmodule.o: basicopsmodule.c roapbops.h roaphelp.h
	$(CC) $(CFLAGS) -c basicopsmodule.c

helpmodule.o: helpmodule.c roaphelp.h
	$(CC) $(CFLAGS) -c helpmodule.c


#remove object files and emac backup files from directory before forcing recompilation
clean:
	$(RM) count *.o *~
