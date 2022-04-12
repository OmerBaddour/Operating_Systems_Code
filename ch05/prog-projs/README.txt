sleeping_ta.c

This is a famous synchronization problem worth Googling.

A sleepy TA helps students complete an assignment.

When a student arrives, they take a seat. There are only 3 seats. If a student
arrives and there are no seats, they resume working on the assignment. If they
are the first student in line, they wake up the sleeping TA to get help. The
TA is woken up with a TA semaphore.

The TA helps students one at a time in a FIFO manner. The queue is managed by
a student semaphore. The queue size is regulated with a mutex-protected integer
variable.

I think the key to solving this problem is to realize which events must have a
specific order:
	- Students must request help before the TA can help them
	- Students being helped must wait until the TA is done helping them
This order can be enforced with synchronization primitives. Section 5.6.1
shows how to do this with semaphores.

To spice up the assignment, I added some randomization. The students have to
complete at least MAX_ASSIGNMENT_TIME / 2 work, and at most MAX_ASSIGNMENT_TIME
work. A random number is sampled in this range. It is compared to the total
time spent working by the student, plus 10 times the number of times they have
been helped by the TA, all multiplied by the student's intelligence (random 
float with bounds [1, 2]), to determine whether the student has 
completed the assignment.

All students eventually finish the assignment. When this occurs,
I kill the TA thread, leaving the TA in a peaceful slumber, until the 
day before the next assignment's deadline, of course.

$ make sleeping_ta

-------------------------------------------------------------------------------

dining_philosophers.c


This is also a famous synchronization problem worth Googling.

Dining philosophers spend their time thinking or eating. They are forced to
share forks. The program guarantees that no two philosophers are using the 
same fork at the same time. Furthermore, the program prevents starvation; all
philosophers will eventually eat.

The textbook provides a solution that guarantees fork mutual exclusion, but
does not prevent deadlock or starvation. I decided to build on top of the book's
informal suggestion of using the order that forks are handled to prevent
deadlock.

All philosophers have an ID. Philosophers with an odd ID who wish to eat grab
the right fork, then the left. Philosophers with an even ID who wish to eat grab
the left fork, then the right. This prevents deadlock, since the case that all 
philosophers have one fork, and are waiting for another, cannot occur.

I believe my solution also prevents against starvation. Condition variables are
used to track a queue of philosophers for each fork. So, if philosopher 0 is
using fork 0 and is done, and philosopher 1 is waiting for fork 0, philosopher 1
is guaranteed to get fork 0 next. Philosopher 1 cannot skip philosopher 0 to get
fork 0 again.

$ make dining_philosophers

-------------------------------------------------------------------------------

