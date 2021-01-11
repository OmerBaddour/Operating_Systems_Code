shm-posix-producer and shm-posix-consumer:

Test the writing to and reading of shared memory. First run fig3-17 in one
window, and then run fig3-18 in another window, to print the written text
to stdout.

--------------------------------------------------------------------------------

unix_pipe:

Test the creation of an ordinary pipe, which is used to write data to the child 
process from the parent process.

--------------------------------------------------------------------------------

fig3-30, multi-fork, fig3-32, -33, -34, -35:

Test fork() stuff.
Note: n sequential calls to fork() results in 2^n processes
Note: a for loop which repeats n times, and calls fork() in each iteration, 
results in 2^n processes
Explanation: fork() doubles the number of processes present.

