shm-posix-producer.c and shm-posix-consumer.c:

Test the writing to and reading of shared memory. First run shm-posix-producer.c
in one window, and then run shm-posix-consumer.c in another window, to print the
written text to stdout.

$ make shm

--------------------------------------------------------------------------------

unix_pipe.c:

Test the creation of an ordinary pipe, which is used to write data to the child 
process from the parent process.

$ make unix_pipe

--------------------------------------------------------------------------------

fig3-30.c, multi-fork.c, fig3-32.c, -33.c, -34.c, -35.c:

Test fork() stuff.
Note: n sequential calls to fork() results in 2^n processes
Note: a for loop which repeats n times, and calls fork() in each iteration, 
results in 2^n processes
Explanation: fork() doubles the number of processes present.

$ make fig3-30 fig3-32 ...

--------------------------------------------------------------------------------

simple-shell.c

Simple shell program. Slightly modified from textbook implementation: deleted
should_run variable, and replaced with an infinite loop with a break case.

$ make simple-shell
