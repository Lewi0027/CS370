# Provided Makefile-1
#CC = clang
# CFLAGS += -Wall

# all: checker coordinator

# checker: checker.c
# 	$(CC) $(CFLAGS) $< -o $@

# coordinator: coordinator.c
# 	$(CC) $(CFLAGS) $< -o $@

# clean:
# 	rm -f checker coordinator

#list of files 
C_SRCS = coordinator.c checker.c
C_OBJS = coordinator.o checker.o
C_HEADERS = coordinator.h 

OBJS = ${C_OBJS}
EXE1 = coordinator
EXE2 = checker

#compiler and loader commands and flags 
GCC = gcc
GCC_FLAGS = -std=c11 -g -Wall -c -I.
LD_FLAGS = -std=c11 -g -Wall -I.

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $<
	
#target is the executable 
all: coordinator checker
coordinator: coordinator.o 
	$(GCC) $(LD_FLAGS) coordinator.o -o $(EXE1)
checker:  checker.o
	$(GCC) $(LD_FLAGS) checker.o -o $(EXE2)
	
#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS}

#clean up directory 
clean: 
	rm -f *.o *- $(EXE1) $(EXE2)
package: 
	zip -r Henry-Lewis-HW3.zip coordinator.c coordinator.h checker.c Makefile README.txt