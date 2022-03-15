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

--------------------------------------------------------------------------------

primes.c

Prints all primes less than or equal to the enterred command line argument using
the Sieve of Eratosthenes.

$ make primes
$ ./primes n

--------------------------------------------------------------------------------

DateServer.java and DateClient.java

DateServer.java is multithreaded.
DateClient.java is identical to that in ch3/

$ make Date
In one shell session: $ java DateServer
In another shell session: $ java DateClient

--------------------------------------------------------------------------------

fibonacci.c

Prints first n Fibonacci numbers, where n is a command line argument.

$ make fibonacci
$ ./fibonacci n

--------------------------------------------------------------------------------

EchoServer.java and EchoClient.java

EchoServer.java is multithreaded.
EchoClient.java is identical to that in ch3/prog-probs/

$ make Echo
In one shell session: $ java EchoServer
In another shell session: $ java EchoClient

--------------------------------------------------------------------------------

