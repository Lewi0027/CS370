package synchronizedBlock;

public class SyncMain {
    
    public static void main (String[] args) {

        int[] sharedResource = new int[42]; // Could create a new class with this as a variable

        SyncWorker worker1 = new SyncWorker(sharedResource);
        SyncWorker worker2 = new SyncWorker(sharedResource);

        Thread t1 = new Thread(worker1);
        Thread t2 = new Thread(worker2);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("ERROR");
        }

        System.out.println("All threads complete.");
    }
}
