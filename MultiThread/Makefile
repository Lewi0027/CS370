FILES = ThreadMain.java Worker.java
all:
	javac -d .. ./$(FILES)
run:
	java -cp .. MultiThread.ThreadMain
clean:
	rm -f ../MultiThread/*.class
package:
	zip -r MultiThread.zip $(FILES) Makefile README.txt