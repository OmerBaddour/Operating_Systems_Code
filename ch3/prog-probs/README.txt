zombie.c: p3-19

Creates zombie process for at least 10 seconds. Child process terminates 
immediately after fork(), but parent process sleep()s for 10 seconds without
wait()ing for child process to terminate.

Run the program in the background with $ ./p3-19 &
Observe the zombie process with $ ps -l  

--------------------------------------------------------------------------------

pid_manager.c and pid_manager.h: p3-20

API for obtaining and releasing PIDs

Investigate behaviour with pid_requester $ make pid_requester

--------------------------------------------------------------------------------

collatz.c: p3-21

Spawns a child process that executes the algorithm associated with the Collatz
conjecture. The sequence is printed to stdout.

$ make collatz
$ ./collatz <positive_integer>

--------------------------------------------------------------------------------

shm_collatz.c: p3-22

Same as collatz.c, except child process writes to shared memory instead of 
stdout. Parent then reads shared memory contents and writes to stdout.

