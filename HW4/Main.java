package HW4;

public class Main {
    
    public static final int iterations = 1000000;
    public static void main(String[] args) {

        //Create a buffer item along with a producer and consumer instantiation
        Buffer buffer = new Buffer(1000);
        Producer producer = new Producer(buffer, iterations);
        Consumer consumer = new Consumer(buffer, iterations);

        //Create a thread for both the producer and consumer; 1 of each
        Thread prodThread = new Thread(producer);
        Thread consThread = new Thread(consumer);

        //Start each thread
        prodThread.start();
        consThread.start();

        //Attempt to join the threads after they are done running.
        try {
            prodThread.join();
            consThread.join();
        } catch (InterruptedException e) {
            System.out.println("ERROR IN MAIN.\n");
        }
        System.out.println("Exiting!\n");
    }
}
