#define MIN_PID 300
#define MAX_PID 5000 

// inclusive of bounds
#define LEN_PIDS MAX_PID - MIN_PID + 1

/* create and initialize structure representing PIDs
 * returns 1 if successful, -1 if unsuccessful */ 
int allocate_map(void);

/* allocates and returns a PID 
 * returns -1 if unsuccessful (all PIDs in use) */ 
int allocate_pid(void);

/* releases a PID */
void release_pid(int pid);
