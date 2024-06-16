Producer Consumer problem:
1. Bounded buffer: n = 1000; FIFO; circular buffer
2. Producer: If buffer full producer must wait; Make a total of 1,000,000 items (random Double generated using java.util.Random)
3. Consumer: If buffer empty consumer must wait; consume all (1,000,000) elements

* Only one instance of buffer, producer and consumer.
* Can only use wait() and notify() as primitives to synchronize access to the buffer.