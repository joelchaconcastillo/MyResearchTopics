# Makefile for PREMO

# Compiler
CC = gcc

# Compiler options
CFLAGS = -g -Wall 

# all object files
SEL_OBJECTS = hyp_ind.o premo_wdfs.o

all: hyp_ind

hyp_ind: $(SEL_OBJECTS)
	$(CC) $(CFLAGS) -lm $(SEL_OBJECTS) -o hyp_ind

premo_wdfs.o: premo_wdfs.c premo_wdfs.h
	$(CC) $(CFLAGS) -c premo_wdfs.c 

hyp_ind.o : hyp_ind.c premo_wdfs.h
	$(CC) $(CFLAGS) -c hyp_ind.c

clean:
	rm -f *~ *.o


