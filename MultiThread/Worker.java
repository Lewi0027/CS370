package MultiThread;

public class Worker implements Runnable {
    
    public String name;

    public Worker(String name) {
        this.name = name;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println("Hello from thread named " + name + " index = " + i);
        }
    }
}
