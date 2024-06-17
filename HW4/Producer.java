import java.util.Random;

public class Producer implements Runnable {
    
    private Buffer buffer;
    private Random random;
    private int iterations;

    //Import buffer item and create Random item for generating doubles
    public Producer(Buffer buffer, int iterations) {
        this.buffer = buffer;
        this.random = new Random();
        this.iterations = iterations;
    }
    
    //Loop to create 1,000,000 items and add them to the buffer
    //Maintain total value for outputting
    @Override
    public void run() {
        double total = 0d;
        for (int i = 0; i < iterations; i++) {
            double bufferElement = random.nextDouble() * 100.0;
            
            try {
                buffer.produce(bufferElement);
                total += bufferElement;
            } catch (InterruptedException e) {
                System.out.println("ERROR in PRODUCER.");
            }

            if (i % 100000 == 0 && i != 0) {
                System.out.println("Producer: Generated " + i/1000 + ",000 items, Cumulative value of generated items=" + formatDouble(total));
            }
            if (i == iterations - 1) {
                System.out.println("Producer: Generated 1,000,000 items, Cumulative value of generated items=" + formatDouble(total));
            }
        }
        // System.out.println("Producer: Finished generating 1,000,000 items");
    }

    private String formatDouble(double value) {
        return String.format("%.3f", value);
    }
}