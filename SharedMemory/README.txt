1. Get and Write shared memory ID to pipe
2. Use execlp(), read from Child process
3. Write to shared memory segment in child process, detach from shared memory segment and return
4. Parent process waits for child process; comes off waits
5. Parent attaches to shared memory segment; read/print necessary stuff
6. Destroy the shared memory segment
