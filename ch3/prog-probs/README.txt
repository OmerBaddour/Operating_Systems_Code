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

--------------------------------------------------------------------------------

QOTDServer.java and QOTDClient.java: p3-23

Same as ../DateServer.java and ../DateClient.java, with changes to port and msg

$ make QOTD

--------------------------------------------------------------------------------

HaikuServer.java and HaikuClient.java: p3-24

Same as ../DateServer.java and ../DateClient.java, with changes to port and msg

$ make Haiku

--------------------------------------------------------------------------------

EchoServer.java and EchoClient.java: p3-25

Echo client reads bytes from stdin and sends through the socket to Echo server.
Echo server prints bytes and echoes bytes back to client, who also prints bytes.

Feel like my client implementation is a little shitty...

$ make Echo

--------------------------------------------------------------------------------

reverse.c: p3-26

Uses ordinary pipes to send a message, reverse the case of the message, and send
the reversed case message back to the sender.

$ make reverse_case
