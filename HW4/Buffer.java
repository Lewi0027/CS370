public class Buffer {
    
    private double[] array;
    private int empty;
    private int full;
    private int capacity;

    //Initialize values
    public Buffer(int capacity) {
        this.capacity = capacity;
        this.array = new double[capacity];
        this.empty = capacity;
        this.full = 0;
    }

    //Produce method
    //Check if full; add value to array; notify()
    synchronized public void produce(double value) throws InterruptedException {
        while (full == capacity) {
            wait();
        }

        array[full] = value;
        full++;
        empty--;
        notify();
    }

    //Consume method
    //Check if empty; remove value from array; notify()
    synchronized public double consume() throws InterruptedException {
        while (empty == capacity) {
            wait();
        }

        double retValue = array[capacity - empty - 1];
        array[capacity - empty - 1] = 0d;
        full--;
        empty++;
        notify();
        
        return retValue;
    }
}