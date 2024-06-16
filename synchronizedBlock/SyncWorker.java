package synchronizedBlock;

public class SyncWorker implements Runnable {
    
    private int[] sharedResource;

    public SyncWorker(int[] sharedResource) {
        this.sharedResource = sharedResource;
    }

    public void run() {
        synchronized(this.sharedResource) {
            // Acess the vairables by index
            // Set indices
        }
    }
}
