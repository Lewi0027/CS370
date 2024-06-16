package HW4;

public class Consumer implements Runnable {

    private Buffer buffer;
    private int iterations;

    //Import buffer item
    public Consumer(Buffer buffer, int iterations) {
        this.buffer = buffer;
        this.iterations = iterations;
    }

    //Loop to remove 1,000,000 items from the buffer
    //Maintain total value for outputting
    @Override
    public void run() {
        double total = 0d;
        for (int i = 0; i < iterations; i++) {
            try {
                double bufferElement = buffer.consume();
                total += bufferElement;
            } catch (InterruptedException e) {
                System.out.println("ERROR in CONSUMER.\n");
            }

            if (i % 100000 == 0 && i != 0) {
                System.out.println("Consumer: Consumed " + i/1000 + ",000 items, Cumulative value of consumed items=" + formatDouble(total));
            }
        }
        System.out.println("Consumer: Finished consuming 1,000,000 items");
    }

    private String formatDouble(double value) {
        return String.format("%.3f", value);
    }
}
