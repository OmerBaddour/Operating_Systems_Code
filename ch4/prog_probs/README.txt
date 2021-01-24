pid_requester.c

Requests PIDs using the API created in the chapter 3 programming problems.
The chapter 3 files are included in this directory for convenience.
The program uses as many threads as there are cores on the host machine.

$ make pid_requester

--------------------------------------------------------------------------------

stats.c

Writes the average, max and min of command line arguments.
The command line arguments must be positive integers (done for simplicity).
The program creates a new thread for each statistical property.

$ make stats

--------------------------------------------------------------------------------

pi_mc_1.c

Creates a thread that computes the value of pi using the Monte Carlo method.

$ make pi_mc_1

--------------------------------------------------------------------------------

pi_mc_2.c

Creates many threads to compute the value of pi using the Monte Carlo method.
Each thread is responsible for the creation of one point.

$ make pi_mc_2
