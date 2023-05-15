# OS-Simulator
Compile code using: `g++ -std=c++17 *.cpp -o runme`

CPU scheduling is priority-based. Every process has a priority number. The higher is the number, the higher is priority. The process with higher priority uses the CPU. The scheduling is preemptive. It means that if a process with the higher priority arrives to the ready-queue while a lower-priority process uses the CPU, the lower-priority process is preempted (that is moved back to ready-queue) while the higher priority process immediately starts using the CPU. Pay attention, higher-priority process never waits in the ready-queue while lower-priority process uses the CPU.
If there are two or more processes with the same highest priority in the ready-queue, your system can schedule any of them to the CPU.

Memory management uses contiguous memory allocation with the “best-fit” approach. The description of “best fit” contiguous memory allocation will be given in class and is also available in our textbook.
I can ask your library to simulate large amounts of memory (say 64 GB or even more). C++ datatype unsigned long long should be able to store such numbers.
It is not allowed to represent each byte of memory individually. For example, it is not allowed to use vector with 1000 elements to represent 1000 bytes of memory.
When multiple memory holes simultaneously satisfy “best fit” condition, use the first one (the one with the smallest memory address).
 
Disk management is “first-come-first-served”. In other words, all disk I/O-queues are real queues (FIFO).
