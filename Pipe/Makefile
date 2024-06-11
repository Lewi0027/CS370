#list of files 
C_SRCS = Pipe.c Child.c
C_OBJS = Pipe.o Child.o
#C_HEADERS 

OBJS = ${C_OBJS}
EXE1 = pipe
EXE2 = child

#compiler and loader commands and flags 
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS = -std=c11 -g -Wall -I.

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $<
	
#target is the executable 
all: pipe child 
pipe: Pipe.o 
	$(GCC) $(LD_FLAGS) Pipe.o -o $(EXE1)
child:  Child.o
	$(GCC) $(LD_FLAGS) Child.o -o $(EXE2)
	
#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS}

#clean up directory 
clean: 
	rm -f *.o *- $(EXE1) $(EXE2)
package: 
	zip -r Henry-Lewis-HW2.zip Pipe.c Child.c Makefile README.txt