package MultiThread;
public class ThreadMain {

    public static void main(String[] args) {

        System.out.println("Starting main trhead...\n");

        Worker susan = new Worker("Susan");
        Worker bob = new Worker("Bob");

        Thread susanThread = new Thread(susan);
        Thread bobThread = new Thread(bob);

        susanThread.start();
        bobThread.start();

        try {
            susanThread.join();
            bobThread.join();
        } catch (InterruptedException e) {
            System.out.println("Interrupted Exception was caught.");
        }

        System.out.println("Alll threads complete.");
    }

}