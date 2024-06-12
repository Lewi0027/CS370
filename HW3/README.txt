HW3:

1. Modify checker to take an aditional argument (buffer)
2. Create a pipe for each child. Also create a shared memory segment.
3. Pass divisor, dividend and pipe to child through execlp
4. Use pipe to pass shared memory segment to child and return either 0 or 1 if divisble.
5. Have parent wait for each child and then read value from shared memory.
