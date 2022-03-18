#include <semaphore.h>

#define MAX_RESOURCES 5

/* initialize the semaphore */
void init_sem(void);

/* decrease the number of resources */
int decrease_count(int);

/* increase the number of resources */
int increase_count(int);

/* clean up semaphore */
void free_sem(void);

