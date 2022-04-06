/* initialize barrier */
void init(int);

/* halt until all threads have reached the barrier point */
/* custom decision: returns nothing */
void barrier_point(void);

/* clean up resources */
void clean_up(void);

