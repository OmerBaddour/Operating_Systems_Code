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

Requests resource from the resource manager in a race-condition-proof way.

$ make resource_requester

