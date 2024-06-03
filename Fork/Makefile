#list of files 
C_SRCS = Fork.c ChildTask.c
C_OBJS = Fork.o ChildTask.o
#C_HEADERS 

OBJS = ${C_OBJS}
EXE1 = fork
EXE2 = childTask

#compiler and loader commands and flags 
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS = -std=c11 -g -Wall -I.

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $<
	
#target is the executable 
all: fork childTask 
fork: Fork.o 
	$(GCC) $(LD_FLAGS) Fork.o -o $(EXE1)
childTask:  ChildTask.o
	$(GCC) $(LD_FLAGS) ChildTask.o -o $(EXE2)
	
#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS}

#clean up directory 
clean: 
	rm -f *.o *- $(EXE1) $(EXE2)
package: 
	zip -r Henry-Lewis-HW2.zip Fork.c ChildTask.c Makefile README.txt