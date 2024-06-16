package HW4;

public class Buffer {
    
    private double[] array;
    private int in;
    private int out;
    private int capacity;
    private boolean full;
    private boolean empty;

    //Initialize values
    public Buffer(int capacity) {
        this.capacity = capacity;
        this.array = new double[capacity];
        this.in = 0;
        this.out = 0;
        this.full = false;
        this.empty = true;
    }

    //Produce method
    //Check if full; add value to array; notify()
    synchronized public void produce(double value) throws InterruptedException {
        while (full) {
            wait();
        }

        array[in % this.capacity] = value;
        in++;
        if (in - out == this.capacity) {
            full = true;
        }
        empty = false;
        notify();
    }

    //Consume method
    //Check if empty; remove value from array; notify()
    synchronized public double consume() throws InterruptedException {
        while (empty) {
            wait();

        }

        double retValue = array[out % capacity];
        array[out % capacity] = 0;
        out++;
        if (in == out) {
            empty = true;
        }
        full = false;
        notify();
        
        return retValue;
    }

}
