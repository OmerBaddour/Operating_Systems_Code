typedef int buffer_item;
#define BUFFER_SIZE 5

void init_buffer(void);
int insert_item(buffer_item);
int remove_item(buffer_item *);
void clean_buffer(void);

