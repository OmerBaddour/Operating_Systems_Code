#define MAX_RESOURCES 5

/* initialize the monitor */
void init_monitor(void);

/* decrease the number of resources
 * now does not return the number of resources */
void decrease_count(int);

/* increase the number of resources */
int increase_count(int);

/* clean up the monitor */
void free_monitor(void);

