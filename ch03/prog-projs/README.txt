simple-shell.c

Simple shell program. Slightly modified from textbook implementation: deleted
should_run variable, and replaced with an infinite loop with a break case.

$ make simple-shell

--------------------------------------------------------------------------------

tasks.c

Kernel module which lists the name, state and PID of all tasks currently running.
Does depth-first search starting with the init task.

$ make tasks
$ sudo insmod tasks.ko
$ dmesg
$ sudo rmmod tasks

