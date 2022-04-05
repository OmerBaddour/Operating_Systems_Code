pid_requester.c, pid_manager.c

Requests PIDs using the API created in the chapter 3 and 4 programming
problems. The chapter 4 files are included in this directory for convenience.
The program uses as many threads as there are cores on the host machine.

$ make pid_requester

-------------------------------------------------------------------------------

pid_requester_2.c, pid_manager_2.c

Requests PIDs using the API created in the chapter 3 and 4 programming
problems. The chapter 4 files are included in this directory for convenience.
The program uses as many threads as there are cores on the host machine.

This differs from pid_requester.c in the sense that the mutex lock lives in the
pid_manager process, and is not shared by each of the requesting threads of
pid_requester. This is probably the better way to solve this problem.

$ make pid_requester_2

-------------------------------------------------------------------------------

resource_requester.c, resource_manager.c

Requests resources from the resource manager in a race-condition-proof way.

$ make resource_requester

-------------------------------------------------------------------------------

resource_requester_monitor.c, resource_manager_monitor.c

Requests resources from the resource manager, which is implemented as a monitor.

I didn't feel the textbook did a great job of preparing the reader for this
question. Here are some useful resources:

- Simulating a monitor, and an explanation on the importance of static variables
  - http://www.csl.mtu.edu/cs4411.ck/www/NOTES/threads/sim-mon.html
- A code example with condition variables
  - https://stackoverflow.com/questions/3827598/how-can-i-code-a-monitor-in-c
- Good holistic condition documentation
  - https://www.ibm.com/docs/en/i/7.1?topic=ssw_ibm_i_71/apis/users_75.htm
- A nice condition variable in Linux guide
  - https://tuxthink.blogspot.com/2013/01/using-condition-variables-in-pthreads.html
- A nice detailed conceptual explanation of condition variables
  - https://stackoverflow.com/questions/47804723/how-exactly-does-the-wait-function-work-in-regards-to-condition-variables

$ make resource_requester_monitor
