# Assignment 1

## Files
- *threading_simple.c*: Simple threading program with a race condition.
- *threading_mutex.c*: Simple Threading program with mutex to fix race condition.
- *threading_complex.c*: Complex threaded simulator using task synchronization.
- *cbmc_complex.out*: output from running CBMC on threading_complex.c

## threading_simple.c

CBMC correctly verifies the program.  Each thread increments the global variable g.  g is affected by the threaded race condition, and therefore could be in a range from 0 to the number of threads. Making the verify bound smaller will cause CBMC to find a solution.

## threading_mutex.c
CBMC correctly verifies the program.  Each thread increments the global variable g, but this time uses a mutex to limit access to g.  g is not affected by the threaded race condition, and therefore g is equal to the number of threads. Changing the assert finds a solution for other values.

## threading_complex.c
CBMC has problems with this program. The program creates 4 threads; deerThread, grainThread, invasiveThread, and watchThread. The deerThread, grainThread, and invasiveThread are on infinite loops, and using barriers to coordinate. The watchThread watches the simulation and exits when it hits the end. The main thread is waiting on the watchThread to exit, and when it does, it cancels the other 3 threads. I modified the program to run 1 loop with unwinding set at 2. It took 6 minutes to run and returned with an unwinding assertion from the grainThread. The grainThread is one of the threads that is in an infinite loop, and therefore never really exited the loop.


