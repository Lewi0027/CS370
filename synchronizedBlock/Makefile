FILES = SyncMain.java SyncWorker.java
all:
	javac -d .. ./$(FILES)
run:
	java -cp .. synchronizedBlock.SyncMain
clean:
	rm -f ../synchronizedBlock/*.class
package:
	zip -r SynchronizedBlock.zip $(FILES) Makefile README.txt