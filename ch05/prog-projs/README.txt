sleeping_ta.c

A sleepy TA helps students complete an assignment.

When a student arrives, they take a seat. There are only 3 seats. If a student
arrives and there are no seats, they resume working on the assignment. If they
are the first student in line, they wake up the sleeping TA to get help. The
TA is woken up with a TA semaphore.

The TA helps students one at a time in a FIFO manner. The queue is managed by
a student semaphore. The queue size is regulated with a mutex-protected integer
variable.

To spice up the assignment, I added some randomization. The students have to
complete at least MAX_ASSIGNMENT_TIME / 2 work, and at most MAX_ASSIGNMENT_TIME
work. A random number is sampled in this range. It is compared to the total
time spent working by the student, plus 10 times the number of times they have
been helped by the TA, all multiplied by the student's intelligence (random 
float with [1, 2) as its bounds), to determine whether the student has 
completed the assignment.

All students eventually finish the assignment. When this occurs,
I kill the TA thread, leaving the TA in a peaceful slumber, until the 
day before the next assignment's deadline, of course.

$ make sleeping_ta

-------------------------------------------------------------------------------

