CC=gcc
FILES=Driver.c MemoryManager.c
OUT_EXE = Driver
all: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o $(OUT_EXE)
package: 
	zip -r Henry-Lewis-HW1.zip Driver.c MemoryManager.h MemoryManager.c Makefile README.txt
